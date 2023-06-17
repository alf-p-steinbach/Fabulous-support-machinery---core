#include <fsm/core.hpp>
#include <fsm/$-macros.hpp>

namespace fsm = fabulous_support_machinery;

#include <winapi-header-wrappers/windows-h.for-utf-16.hpp>
#ifdef _MSC_VER
#   pragma comment( lib, "user32.lib" )
#endif

#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <map>
#include <mutex>
#include <queue>
#include <string>
#include <tuple>
#include <utility>
using namespace std::literals;

#include <assert.h>

namespace winapi {
    using   fsm::hopefully, fsm::int_size_of, fsm::Movable, fsm::in_;
    using   std::exchange;                  // <utility>

    //---------------------------------------------------------- Streams:

    namespace stream_handle {
        // inline const_<HANDLE>  in   = GetStdHandle( STD_INPUT_HANDLE );
        // inline const_<HANDLE>  out  = GetStdHandle( STD_OUTPUT_HANDLE );
        // inline const_<HANDLE>  err  = GetStdHandle( STD_ERROR_HANDLE );
        
        inline const HANDLE in   = ::CreateFile(
            L"CONIN$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0
            );
    }  // namespace stream_handle


    //---------------------------------------------------------- Threading support:

    class Signal:
        public Movable
    {
        HANDLE  m_event_handle;
        
    public:
        ~Signal() { ::CloseHandle( m_event_handle ); }

        Signal():
            // Creating a "manual reset" event object.
            m_event_handle( ::CreateEvent( nullptr, true, false, nullptr ) )
        {
            hopefully( m_event_handle != 0 ) or $fail( "CreateEvent failed" );
        }
        
        Signal( Signal&& other ):
            m_event_handle( exchange( other.m_event_handle, +HANDLE() ) )
        {}
        
        auto handle() const -> HANDLE { return m_event_handle; }
        void send() { ::SetEvent( m_event_handle ); }
    };


    //---------------------------------------------------------- Console io events:

    using Key_code = WORD;
    struct Event_kind{ enum Enum{ console_event, signal }; };

    void wait_for_events()
    {
        ::WaitForSingleObject( stream_handle::in, INFINITE )
            >> $expect( retval == WAIT_OBJECT_0 )
            or $fail( "::WaitForSingleObject failed unexpectedly." );
    }

    auto wait_for_events_or( in_<Signal> abort_request_signal )
        -> Event_kind::Enum
    {
        const HANDLE handles[] =
        {
            stream_handle::in,
            abort_request_signal.handle()
        };
        constexpr int begin_ok_range    = WAIT_OBJECT_0;
        constexpr int end_ok_range      = begin_ok_range + int_size_of( handles );
        const int retval = ::WaitForMultipleObjects( int_size_of( handles ), handles, false, INFINITE );
        hopefully( begin_ok_range <= retval and retval < end_ok_range )
            or $fail( "::WaitForMultipleObjects failed unexpectedly." );
        const int handles_index = retval - WAIT_OBJECT_0;
        return static_cast<Event_kind::Enum>( handles_index );
    }

    auto event_count()
        -> int
    {
        DWORD n_events = 0;
        ::GetNumberOfConsoleInputEvents( stream_handle::in, &n_events )
            or $fail( "::GetNumberOfConsoleInputEvents failed unexpectedly." );
        return static_cast<int>( n_events );
    }

    auto next_event()
        -> INPUT_RECORD
    {
        INPUT_RECORD    result;
        DWORD           n_read  = 0;

        ::ReadConsoleInput( stream_handle::in, &result, 1, &n_read )
            or $fail( "::ReadConsoleInput failed unexpectedly." );
        assert( n_read == 1 );
        return result;
    }
    
    auto is_pressed_now( const Key_code key_code )
        -> bool
    { return (::GetAsyncKeyState( key_code ) < 0); }
}  // namespace winapi

namespace console_io_event_server {
    $using_nsname( std, this_thread );
    using namespace fsm::type_builders;         // `in_`, etc.
    using   fsm::is_empty, fsm::Default_value, fsm::Shared_queue_, fsm::Joining_thread;
    using   std::atomic,                        // <atomic>
            std::clog, std::endl,               // <iostream>
            std::map,                           // <map>
            std::ref;                           // <utility>
    using   winapi::Key_code, winapi::Signal;

    using Key_code_set  = std::set<Key_code>;

    auto key_code_of( in_<KEY_EVENT_RECORD> ev )
        -> Key_code
    { return ev.wVirtualKeyCode; }

    auto is_keypress( in_<KEY_EVENT_RECORD> ev )
        -> bool
    { return !!ev.bKeyDown; }

    auto is_key_release( in_<KEY_EVENT_RECORD> ev )
        -> bool
    { return not ev.bKeyDown; }
    
    auto key_code_of( in_<INPUT_RECORD> ev )
        -> Key_code
    { return (ev.EventType == KEY_EVENT? key_code_of( ev.Event.KeyEvent ) : 0); }

    class Down_key_set
    {
        map<Key_code, INPUT_RECORD>     m_up_events;

    public:
        friend auto is_empty( in_<Down_key_set> dks )
            -> bool
        { return is_empty( dks.m_up_events ); }

        auto contains( const Key_code key_code ) const
            -> bool
        { return (m_up_events.find( key_code ) != m_up_events.end()); }

        void add( in_<KEY_EVENT_RECORD> event )
        {
            const auto [it, was_added] = m_up_events.insert( {
                key_code_of( event ), INPUT_RECORD{ KEY_EVENT, event }
                } );
            if( was_added ) { it->second.Event.KeyEvent.bKeyDown = false; }
        }

        void remove( const Key_code key_code )
        {
            m_up_events.erase( key_code );
        }

        void clear() { m_up_events.clear(); }

        auto not_actually_pressed_now() const
            -> Key_code_set
        {
            Key_code_set result;
            for( const auto& [key_code, _]: m_up_events ) {
                if( not winapi::is_pressed_now( key_code ) ) {
                    result.insert( key_code );
                }
            }
            return result;
        }
        
        auto up_event_for( const Key_code key_code )
            -> INPUT_RECORD
        { return m_up_events.at( key_code ); }
    };

    void ignore_repeats_with_at_first(
        in_<KEY_EVENT_RECORD>               initial_key_event,
        ref_<Shared_queue_<INPUT_RECORD>>   event_q,
        in_<Signal>                         quit_request_signal
        )
    {
        Down_key_set    down_key_set;
        Key_code        current_repeater    = key_code_of( initial_key_event );

        assert( is_keypress( initial_key_event ) );
        down_key_set.add( initial_key_event );

        while( not is_empty( down_key_set ) ) {
            if( winapi::event_count() == 0 ) {
                Key_code_set released_keys;
                {
                    auto event_q_access = event_q.access();
                    released_keys = down_key_set.not_actually_pressed_now();
                    if( not is_empty( released_keys ) ) {
                        const Key_code last_key_code = *released_keys.rbegin();
                        for( const Key_code key_code: released_keys ) {
                            const bool notify_reader = (key_code == last_key_code);
                            event_q_access.enq( down_key_set.up_event_for( key_code ), notify_reader );
                        }
                    }
                }
                for( const Key_code key_code: released_keys ) {
                    down_key_set.remove( key_code );
                }
                if( ::WaitForSingleObject( quit_request_signal.handle(), 0 ) == WAIT_OBJECT_0 ) {
                    // Server shutdown requested.
                    break;
                }
                if( not is_empty( down_key_set ) ) {
                    this_thread::sleep_for( 0.02s );
                }
                continue;
            }

            const INPUT_RECORD  ev          = winapi::next_event();
            if( ev.EventType == KEY_EVENT ) {
                const KEY_EVENT_RECORD& key_ev = ev.Event.KeyEvent;
                const Key_code key_code = key_code_of( key_ev );
                if( key_code == current_repeater ) {
                    if( is_keypress( key_ev ) ) {
                        // ignore
                        // TODO: check time since last event?
                    } else if( winapi::is_pressed_now( key_code ) ) {
                        // ignore; it's inconsistent.
                    } else {
                        // key_code == current_repeater and
                        // is_key_release( key_ev ) and not winapi::is_pressed_now( key_code )
                        down_key_set.remove( key_code );
                        current_repeater = 0;
                        event_q.access().enq( ev );
                    }
                } else {  // key_code != current_repeater
                    current_repeater = 0;
                    if( is_keypress( key_ev ) ) {
                        down_key_set.add( key_ev );
                        current_repeater = key_code;
                    } else {
                        down_key_set.remove( key_code );
                    }
                    event_q.access().enq( ev );
                }
            }
        }
    }

    void serve_events(
        in_<Signal>                         quit_request_signal,
        ref_<Shared_queue_<INPUT_RECORD>>   event_q
        )
    {
        // clog << "> Thread::work" << endl;
        // clog << "Server says hello, seeing " << winapi::event_count() << " events." << endl;
        for( ;; ) {
            using Event_kind_enum = winapi::Event_kind::Enum;
            const Event_kind_enum event_kind = winapi::wait_for_events_or( quit_request_signal );
            const bool quit_requested = (event_kind == Event_kind_enum::signal);
            if( quit_requested ) {
                break;
            }

            if( winapi::event_count() <= 2 ) {  // 2: a generated char keypress has down and up events.
                const INPUT_RECORD ev = winapi::next_event();
                event_q.access().enq( ev );
                if( ev.EventType == KEY_EVENT ) {
                    const KEY_EVENT_RECORD& key_ev = ev.Event.KeyEvent;
                    if( key_ev.bKeyDown and winapi::is_pressed_now( key_ev.wVirtualKeyCode ) ) {
                        // A real first keypress, possibly followed by generated keystrokes,
                        // down/up pairs for characters and just key down events for others.
                        ignore_repeats_with_at_first( key_ev, event_q, quit_request_signal );
                        continue;
                    }
                }
            }

            const int n_events = winapi::event_count();
            if( n_events > 0 ) {
                auto event_q_access = event_q.access();
                for( int i = 1; i <= n_events; ++i ) {
                    const INPUT_RECORD ev = winapi::next_event();
                    const bool notify_reader = (i == n_events);
                    event_q_access.enq( ev, notify_reader );
                }
            }
        }
        // clog << "Server terminates." << endl;
    }

    class Server_singleton
    {
        using Self = Server_singleton;

        Server_singleton( in_<Self> ) = delete;
        auto operator=( in_<Self> ) -> Self& = delete;
        
        Shared_queue_<INPUT_RECORD>     m_event_q;
        Signal                          m_quit_request_signal;
        Joining_thread                  m_thread;
        
        Server_singleton():
            m_event_q(),
            m_quit_request_signal(),
            m_thread( serve_events, ref( m_quit_request_signal ), ref( m_event_q ) )
        {}

    public:
        static auto instance()
            -> Self&
        {
            static Self the_instance;
            return the_instance;
        }

        auto queue() -> Shared_queue_<INPUT_RECORD>& { return m_event_q; }

        void please_quit_soon()             { m_quit_request_signal.send(); }
        void rethrow_if_exception() const   { m_thread.rethrow_if_exception(); }
    };
}  // namespace console_io_event_server

void cpp_main()
{
    namespace this_thread = std::this_thread;
    using   fsm::repeat_times, fsm::Joining_thread, fsm::Shared_queue_;
    using   std::atomic,                        // <atomic>
            std::clog, std::endl,               // <iostream>
            std::string,                        // <string>
            std::ref;                           // <utility>

    (void) fsm::type_<const Shared_queue_<int>>().access();
    clog << "Main starting." << endl;
    {
        auto& event_server  = console_io_event_server::Server_singleton::instance();
        auto& event_q       = event_server.queue();

        int wait_count = 0;
        for( bool finished = false; not finished; ) {
            event_server.rethrow_if_exception();
            if( wait_count == 10 ) { wait_count = 0;  clog << "Some time passed.\n"; }
            const bool items_are_available = event_q.access().wait_for_items_for( 0.2s );
            if( not items_are_available ) {
                ++wait_count;
                continue;
            }
            const int n_events = event_q.access().length();
            clog << string( 25, '-' ) << " " << n_events << " events:" << endl;
            repeat_times( n_events, [&] {
                const INPUT_RECORD ev = event_q.access().deq();
                if( ev.EventType == KEY_EVENT ) {
                    const KEY_EVENT_RECORD& key_ev = ev.Event.KeyEvent;
                    const auto& code = key_ev.wVirtualKeyCode;
                    clog << "Key " << (key_ev.bKeyDown? "down" : "up  ") << ": " << code << endl;
                    if( code == 27 and key_ev.bKeyDown ) {
                        clog << "Main program finishing." << endl;
                        event_server.please_quit_soon();
                        finished = true;
                    }
                }
            } );
        }
    }
    clog << "Main finished." << endl;
}

auto main() -> int { return fsm::with_xinfo_to_stderr( cpp_main ); }
