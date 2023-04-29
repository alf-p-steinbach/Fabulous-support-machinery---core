// Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/text-io/exports/console/event-queue.hpp>

// #include <fsm/core/exports/failure.hpp>                                     // hopefully, FSM_FAIL
#include <fsm/core/exports/support-for-collections/set-utility.hpp>         // contains
// #include <fsm/core/exports/support-for-collections/size-functions.hpp>      // is_empty
#include <fsm/core/exports/constructs/flow-control/repeat_times.hpp>        // repeat_times

// #include <fsm/text-io/implementation/os-specific/windows/_stream_handle.hpp>

#include <fsm/@wrapped/os/winapi/exports/windows-h.for-u16.hpp>
#include <fsm/text-io/implementation/os-specific/windows/console/_os/handles.hpp>   // console_input_handle

#include <queue>

// #include <assert.h>

// #include <iostream>
// #include <iomanip>

namespace fabulous_support_machinery::_os {
    namespace fsm = fabulous_support_machinery;
    
    using   fsm::contains, fsm::repeat_times;
    // using   fsm::hopefully;
    using   std::queue;             // <queue>

    inline auto n_queued_api_events()
        -> int
    {
        DWORD n = 0;
        return (::GetNumberOfConsoleInputEvents( console_input_handle(), &n )? n : 0);
    }

    // TODO: get cleaned events from server thread
    inline auto next_api_event()
        -> INPUT_RECORD
    {
        INPUT_RECORD    result;
        DWORD           n_read  = 0;
        ::ReadConsoleInput( console_input_handle(), &result, 1, &n_read )
            or FSM_FAIL( "::ReadConsoleInput failed unexpectedly." );
        assert( n_read == 1 );
        return result;
    }

    inline auto translated_events()
        -> queue<console::Event_holder>&
    {
        static queue<console::Event_holder> the_buffer;
        return the_buffer;
    }

    inline void translate( in_<KEY_EVENT_RECORD> ev )
    {
        const wchar_t u_code = ev.uChar.UnicodeChar;
        if( u_code != 0 ) {
            const DWORD alt_mask    = LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED;
            const DWORD ctrl_mask   = LEFT_CTRL_PRESSED | RIGHT_CTRL_PRESSED;
            const DWORD shift_mask  = SHIFT_PRESSED;
        
            const bool alt_pressed      = !!(ev.dwControlKeyState & alt_mask);
            const bool ctrl_pressed     = !!(ev.dwControlKeyState & ctrl_mask);
            const bool shift_pressed    = !!(ev.dwControlKeyState & shift_mask);

            Key_modifier_set modifiers;
            if( alt_pressed ) { modifiers |= Key_modifier::alt; }
            if( ctrl_pressed ) { modifiers |= Key_modifier::ctrl; }
            if( shift_pressed ) { modifiers |= Key_modifier::shift; }
            
            const auto key_code = Key_code::Enum( ev.wVirtualKeyCode );
            if( alt_pressed == ctrl_pressed ) {
                // Textual. The Alt+Ctrl possibility is AltGr on e.g. a Norwegian keyboard.
                translated_events().emplace(
                    console::Keyboard_unicode_event( key_code, u_code, modifiers )
                    );
            } else {
                // Non-textual.
                if( is_continuous_effect_key( key_code ) ) {
                    translated_events().emplace(
                        console::Keyboard_continuous_effect_key_event(
                            static_cast<Continuous_key_effect::Enum>( key_code ), modifiers
                            )
                        );
                } else {
                    // TODO:
                    translated_events().emplace( console::Keyboard_special_key_event( key_code ) );
                }
            }
        }
    }

    inline void translate( in_<MOUSE_EVENT_RECORD> ev )
    { (void) ev;
    }

    inline void translate( in_<WINDOW_BUFFER_SIZE_RECORD> ev )
    { (void) ev;
    }

    inline void translate( in_<MENU_EVENT_RECORD> ev )
    { (void) ev;
    }

    inline void translate( in_<FOCUS_EVENT_RECORD> ev )
    { (void) ev;
    }

    inline void translate_one_api_event()
    {
        const INPUT_RECORD api_event = next_api_event();
        switch( api_event.EventType ) {
            case KEY_EVENT:                 translate( api_event.Event.KeyEvent );  break;
            case MOUSE_EVENT:               translate( api_event.Event.MouseEvent );  break;
            case WINDOW_BUFFER_SIZE_EVENT:  translate( api_event.Event.WindowBufferSizeEvent );  break;
            case MENU_EVENT:                translate( api_event.Event.MenuEvent );  break;
            case FOCUS_EVENT:               translate( api_event.Event.FocusEvent );  break;
            default: {
                break;      // Should never get here, but who knows what MS will do.
            }
        }
    }

    inline void translate_available_api_events()
    {
        for( ;; ) {
            const int n = n_queued_api_events();
            if( n == 0 ) { break; }
            repeat_times( n, translate_one_api_event );
        }
    }
    
}  // namespace fabulous_support_machinery::_os
