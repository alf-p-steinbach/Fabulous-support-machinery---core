// The keyboard message hook in a distinct thread is not called.

#include <fabulous_support_machinery/core.hpp>
namespace fsm = fabulous_support_machinery;
using   fsm::in_, fsm::hopefully;

#include <winapi-header-wrappers/windows-h.for-utf-16.hpp>

#include <atomic>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <queue>
#include <set>
#include <thread>
using namespace std::literals;

#include <assert.h>     // assert
#include <stdlib.h>     // EXIT_...

namespace stream_handle {
    inline const_<HANDLE>  in   = GetStdHandle( STD_INPUT_HANDLE );
    inline const_<HANDLE>  out  = GetStdHandle( STD_OUTPUT_HANDLE );
    inline const_<HANDLE>  err  = GetStdHandle( STD_ERROR_HANDLE );
}  // namespace stream_handle

namespace winapi {
    using Key_code = WORD;
    
    void wait_for_events()
    {
        ::WaitForSingleObject( stream_handle::in, INFINITE )
            >> FSM_HOPEFULLY( retval == WAIT_OBJECT_0 )
            or FSM_FAIL( "::WaitForSingleObject failed unexpectedly." );
    }

    auto event_count()
        -> int
    {
        DWORD n_events = 0;
        ::GetNumberOfConsoleInputEvents( stream_handle::in, &n_events )
            or FSM_FAIL( "::GetNumberOfConsoleInputEvents failed unexpectedly." );
        return static_cast<int>( n_events );
    }

    auto next_event()
        -> INPUT_RECORD
    {
        INPUT_RECORD    result;
        DWORD           n_read  = 0;

        ::ReadConsoleInput( stream_handle::in, &result, 1, &n_read )
            or FSM_FAIL( "::ReadConsoleInput failed unexpectedly." );
        assert( n_read == 1 );
        return result;
    }
    
    auto is_pressed_now( const Key_code key_code )
        -> bool
    { return (::GetAsyncKeyState( key_code ) < 0); }
}  // namespace winapi

namespace buffered_api_events {
    using   fsm::int_size_of, fsm::is_empty, fsm::popped_top_of;
    using   std::stack;
    using   winapi::Key_code;

    namespace impl {
        stack<INPUT_RECORD>     winapi_event_buffer;
    }  // namespace impl

    void wait_for_available()
    {
        if( not is_empty( impl::winapi_event_buffer ) ) {
            return;
        }
        winapi::wait_for_events();
    }

    auto n_events()
        -> int
    { return int_size_of( impl::winapi_event_buffer ) + winapi::event_count(); }

    auto next()
        -> INPUT_RECORD
    {
        const bool buffered = not is_empty( impl::winapi_event_buffer );
        return (buffered? popped_top_of( impl::winapi_event_buffer ) : winapi::next_event());
    }
    
    void put_back( in_<INPUT_RECORD> ev )
    {
        impl::winapi_event_buffer.push( ev );
    }
}  // namespace buffered_api_events

namespace cleaned_events {
    namespace impl {
        using   fsm::contains, fsm::is_empty, fsm::item_at, fsm::popped_front_of, fsm::repeat_times;
        using   std::queue,
                std::set;

        using Key_code = WORD;

        namespace g {
            queue<INPUT_RECORD>     app_event_q;
            KEY_EVENT_RECORD        previous_key_event      = {};
            KEY_EVENT_RECORD        current_key_event       = {};
        }  // namespace g

        auto winapi_event_count()
            -> int
        { return buffered_api_events::n_events(); }

        auto next_winapi_event()
            -> INPUT_RECORD
        {
            const INPUT_RECORD ev = buffered_api_events::next();
            if( ev.EventType == KEY_EVENT ) {
                g::previous_key_event = g::current_key_event;
                g::current_key_event = ev.Event.KeyEvent;
            }
            return ev;
        }

        void empty_api_event_buffer()
        {
            // Typed or pasted while the app was doing something else.
            // Read up till any possible buffered repeat, ditch the rest.
            const int n_buffered = winapi_event_count();
            Key_code prev_key_down_code = 0;
            bool ditch_keyboard_events = false;
            repeat_times( n_buffered, [&]{
                const INPUT_RECORD ev = next_winapi_event();
                bool enqueue_it = true;
                if( ev.EventType == KEY_EVENT ) {
                    const KEY_EVENT_RECORD& key_ev = ev.Event.KeyEvent;
                    if( key_ev.bKeyDown ) {
                        if( prev_key_down_code and key_ev.wVirtualKeyCode == prev_key_down_code ) {
                            ditch_keyboard_events = true;
                        }
                        prev_key_down_code = key_ev.wVirtualKeyCode;
                    }
                    enqueue_it = not ditch_keyboard_events;
                }
                if( enqueue_it ) { g::app_event_q.push( ev ); }
            } );
        }

        void wait_for_available()
        {
            while( is_empty( g::app_event_q ) ) {
                // A paste can buffer events for all the text. Consume it all to avoid regarding
                // it as happened while the app was doing something else. No auto-repeats.
                const int n_buffered = winapi_event_count();
                repeat_times( n_buffered, [&]{
                    const INPUT_RECORD ev = next_winapi_event();
                    bool enqueue_it = true;
                    if( ev.EventType == KEY_EVENT ) {
                        const KEY_EVENT_RECORD& key_ev = ev.Event.KeyEvent;
                        if( key_ev.bKeyDown ) {
                            const auto& pkev = g::previous_key_event;
                            if( pkev.bKeyDown and pkev.wVirtualKeyCode == key_ev.wVirtualKeyCode ) {
                                // Skip auto-generated non-character key down events.
                                std::clog << "Skipping one key down event code " << pkev.wVirtualKeyCode << "\n";
                                enqueue_it = false;
                            }
                        }
                    }
                    if( enqueue_it ) { g::app_event_q.push( ev ); }
                } );
            }
        }
    }  // namespace impl

    using   fsm::int_size_of, fsm::popped_front_of;

    void wait_for_available()
    {
        impl::empty_api_event_buffer();
        impl::wait_for_available();
    }

    auto n_events()
        -> int
    { return int_size_of( impl::g::app_event_q ) + impl::winapi_event_count(); }

    auto next() -> INPUT_RECORD
    {
        wait_for_available();
        return popped_front_of( impl::g::app_event_q );
    }
}  // namespace cleaned_events

void foo()
{
    using   std::cout, std::endl,
            std::string;

    for( ;; ) {
        cleaned_events::wait_for_available();
        const int n_events = cleaned_events::n_events();
        cout << string( 30, '-' ) << "  " << n_events << " event(s):  " << string( 30, '-' ) << endl;
        std::clog << "Buffered: " << buffered_api_events::impl::winapi_event_buffer.size() << " events.\n";
        for( int i = 1; i <= n_events; ++i ) {
            const INPUT_RECORD ev = cleaned_events::next();
            if( ev.EventType == KEY_EVENT ) {
                const auto& kev = ev.Event.KeyEvent;
                cout << kev.bKeyDown << "  Code: " << unsigned( kev.uChar.UnicodeChar ) << endl;
                
                if( kev.uChar.UnicodeChar == 27 ) {
                    return;
                }
            }
        }
    }
}

auto main() -> int
{
    using   std::exception, std::cerr, std::endl;
    try {
        foo();
        return EXIT_SUCCESS;
    } catch( in_<exception>& x ) {
        cerr << "!" << x.what() << endl;
    }
    return EXIT_FAILURE;
}
