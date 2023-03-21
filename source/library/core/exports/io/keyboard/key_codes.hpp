﻿#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

namespace fabuluous_support_machinery::keyboard {
    // <url: https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes>
    inline namespace key_codes { enum{
        lbutton_key                 =  0x01,    // VK_LBUTTON - Left mouse button
        rbutton_key                 =  0x02,    // VK_RBUTTON - Right mouse button
        cancel_key                  =  0x03,    // VK_CANCEL - Control-break processing
        mbutton_key                 =  0x04,    // VK_MBUTTON - Middle mouse button (three-button mouse)
        xbutton1_key                =  0x05,    // VK_XBUTTON1 - X1 mouse button
        xbutton2_key                =  0x06,    // VK_XBUTTON2 - X2 mouse button
        back_key                    =  0x08,    // VK_BACK - BACKSPACE key
        tab_key                     =  0x09,    // VK_TAB - TAB key
        clear_key                   =  0x0C,    // VK_CLEAR - CLEAR key
        return_key                  =  0x0D,    // VK_RETURN - ENTER key
        shift_key                   =  0x10,    // VK_SHIFT - SHIFT key
        control_key                 =  0x11,    // VK_CONTROL - CTRL key
        menu_key                    =  0x12,    // VK_MENU - ALT key
        pause_key                   =  0x13,    // VK_PAUSE - PAUSE key
        caps_lock_key               =  0x14,    // VK_CAPITAL - CAPS LOCK key
        kana_key                    =  0x15,    // VK_KANA - IME Kana mode
        hanguel_key                 =  0x15,    // VK_HANGUEL - IME Hanguel mode (for compatibility; use HANGUL_key)
        hangul_key                  =  0x15,    // VK_HANGUL - IME Hangul mode
        ime_on_key                  =  0x16,    // VK_IME_ON - IME On
        junja_key                   =  0x17,    // VK_JUNJA - IME Junja mode
        final_key                   =  0x18,    // VK_FINAL - IME final mode
        hanja_key                   =  0x19,    // VK_HANJA - IME Hanja mode
        kanji_key                   =  0x19,    // VK_KANJI - IME Kanji mode
        ime_off_key                 =  0x1A,    // VK_IME_OFF - IME Off
        escape_key                  =  0x1B,    // VK_ESCAPE - ESC key
        convert_key                 =  0x1C,    // VK_CONVERT - IME convert
        nonconvert_key              =  0x1D,    // VK_NONCONVERT - IME nonconvert
        accept_key                  =  0x1E,    // VK_ACCEPT - IME accept
        modechange_key              =  0x1F,    // VK_MODECHANGE - IME mode change request
        space_key                   =  0x20,    // VK_SPACE - SPACEBAR
        page_up_key                 =  0x21,    // VK_PRIOR - PAGE UP key
        page_down_key               =  0x22,    // VK_NEXT - PAGE DOWN key
        end_key                     =  0x23,    // VK_END - END key
        home_key                    =  0x24,    // VK_HOME - HOME key
        left_key                    =  0x25,    // VK_LEFT - LEFT ARROW key
        up_key                      =  0x26,    // VK_UP - UP ARROW key
        right_key                   =  0x27,    // VK_RIGHT - RIGHT ARROW key
        down_key                    =  0x28,    // VK_DOWN - DOWN ARROW key
        select_key                  =  0x29,    // VK_SELECT - SELECT key
        print_key                   =  0x2A,    // VK_PRINT - PRINT key
        execute_key                 =  0x2B,    // VK_EXECUTE - EXECUTE key
        snapshot_key                =  0x2C,    // VK_SNAPSHOT - PRINT SCREEN key
        insert_key                  =  0x2D,    // VK_INSERT - INS key
        delete_key                  =  0x2E,    // VK_DELETE - DEL key
        help_key                    =  0x2F,    // VK_HELP - HELP key
        char_0_key                  =  0x30,    // 0 key
        char_1_key                  =  0x31,    // 1 key
        char_2_key                  =  0x32,    // 2 key
        char_3_key                  =  0x33,    // 3 key
        char_4_key                  =  0x34,    // 4 key
        char_5_key                  =  0x35,    // 5 key
        char_6_key                  =  0x36,    // 6 key
        char_7_key                  =  0x37,    // 7 key
        char_8_key                  =  0x38,    // 8 key
        char_9_key                  =  0x39,    // 9 key
        char_a_key                  =  0x41,    // A key
        char_b_key                  =  0x42,    // B key
        char_c_key                  =  0x43,    // C key
        char_d_key                  =  0x44,    // D key
        char_e_key                  =  0x45,    // E key
        char_f_key                  =  0x46,    // F key
        char_g_key                  =  0x47,    // G key
        char_h_key                  =  0x48,    // H key
        char_i_key                  =  0x49,    // I key
        char_j_key                  =  0x4A,    // J key
        char_k_key                  =  0x4B,    // K key
        char_l_key                  =  0x4C,    // L key
        char_m_key                  =  0x4D,    // M key
        char_n_key                  =  0x4E,    // N key
        char_o_key                  =  0x4F,    // O key
        char_p_key                  =  0x50,    // P key
        char_q_key                  =  0x51,    // Q key
        char_r_key                  =  0x52,    // R key
        char_s_key                  =  0x53,    // S key
        char_t_key                  =  0x54,    // T key
        char_u_key                  =  0x55,    // U key
        char_v_key                  =  0x56,    // V key
        char_w_key                  =  0x57,    // W key
        char_x_key                  =  0x58,    // X key
        char_y_key                  =  0x59,    // Y key
        char_z_key                  =  0x5A,    // Z key
        lwin_key                    =  0x5B,    // VK_LWIN - Left Windows key (Natural keyboard)
        rwin_key                    =  0x5C,    // VK_RWIN - Right Windows key (Natural keyboard)
        apps_key                    =  0x5D,    // VK_APPS - Applications key (Natural keyboard)
        sleep_key                   =  0x5F,    // VK_SLEEP - Computer Sleep key
        numpad0_key                 =  0x60,    // VK_NUMPAD0 - Numeric keypad 0 key
        numpad1_key                 =  0x61,    // VK_NUMPAD1 - Numeric keypad 1 key
        numpad2_key                 =  0x62,    // VK_NUMPAD2 - Numeric keypad 2 key
        numpad3_key                 =  0x63,    // VK_NUMPAD3 - Numeric keypad 3 key
        numpad4_key                 =  0x64,    // VK_NUMPAD4 - Numeric keypad 4 key
        numpad5_key                 =  0x65,    // VK_NUMPAD5 - Numeric keypad 5 key
        numpad6_key                 =  0x66,    // VK_NUMPAD6 - Numeric keypad 6 key
        numpad7_key                 =  0x67,    // VK_NUMPAD7 - Numeric keypad 7 key
        numpad8_key                 =  0x68,    // VK_NUMPAD8 - Numeric keypad 8 key
        numpad9_key                 =  0x69,    // VK_NUMPAD9 - Numeric keypad 9 key
        multiply_key                =  0x6A,    // VK_MULTIPLY - Multiply key
        add_key                     =  0x6B,    // VK_ADD - Add key
        separator_key               =  0x6C,    // VK_SEPARATOR - Separator key
        subtract_key                =  0x6D,    // VK_SUBTRACT - Subtract key
        decimal_key                 =  0x6E,    // VK_DECIMAL - Decimal key
        divide_key                  =  0x6F,    // VK_DIVIDE - Divide key
        f1_key                      =  0x70,    // VK_F1 - F1 key
        f2_key                      =  0x71,    // VK_F2 - F2 key
        f3_key                      =  0x72,    // VK_F3 - F3 key
        f4_key                      =  0x73,    // VK_F4 - F4 key
        f5_key                      =  0x74,    // VK_F5 - F5 key
        f6_key                      =  0x75,    // VK_F6 - F6 key
        f7_key                      =  0x76,    // VK_F7 - F7 key
        f8_key                      =  0x77,    // VK_F8 - F8 key
        f9_key                      =  0x78,    // VK_F9 - F9 key
        f10_key                     =  0x79,    // VK_F10 - F10 key
        f11_key                     =  0x7A,    // VK_F11 - F11 key
        f12_key                     =  0x7B,    // VK_F12 - F12 key
        f13_key                     =  0x7C,    // VK_F13 - F13 key
        f14_key                     =  0x7D,    // VK_F14 - F14 key
        f15_key                     =  0x7E,    // VK_F15 - F15 key
        f16_key                     =  0x7F,    // VK_F16 - F16 key
        f17_key                     =  0x80,    // VK_F17 - F17 key
        f18_key                     =  0x81,    // VK_F18 - F18 key
        f19_key                     =  0x82,    // VK_F19 - F19 key
        f20_key                     =  0x83,    // VK_F20 - F20 key
        f21_key                     =  0x84,    // VK_F21 - F21 key
        f22_key                     =  0x85,    // VK_F22 - F22 key
        f23_key                     =  0x86,    // VK_F23 - F23 key
        f24_key                     =  0x87,    // VK_F24 - F24 key
        numlock_key                 =  0x90,    // VK_NUMLOCK - NUM LOCK key
        scroll_key                  =  0x91,    // VK_SCROLL - SCROLL LOCK key
        lshift_key                  =  0xA0,    // VK_LSHIFT - Left SHIFT key
        rshift_key                  =  0xA1,    // VK_RSHIFT - Right SHIFT key
        lcontrol_key                =  0xA2,    // VK_LCONTROL - Left CONTROL key
        rcontrol_key                =  0xA3,    // VK_RCONTROL - Right CONTROL key
        lmenu_key                   =  0xA4,    // VK_LMENU - Left ALT key
        rmenu_key                   =  0xA5,    // VK_RMENU - Right ALT key
        browser_back_key            =  0xA6,    // VK_BROWSER_BACK - Browser Back key
        browser_forward_key         =  0xA7,    // VK_BROWSER_FORWARD - Browser Forward key
        browser_refresh_key         =  0xA8,    // VK_BROWSER_REFRESH - Browser Refresh key
        browser_stop_key            =  0xA9,    // VK_BROWSER_STOP - Browser Stop key
        browser_search_key          =  0xAA,    // VK_BROWSER_SEARCH - Browser Search key
        browser_favorites_key       =  0xAB,    // VK_BROWSER_FAVORITES - Browser Favorites key
        browser_home_key            =  0xAC,    // VK_BROWSER_HOME - Browser Start and Home key
        volume_mute_key             =  0xAD,    // VK_VOLUME_MUTE - Volume Mute key
        volume_down_key             =  0xAE,    // VK_VOLUME_DOWN - Volume Down key
        volume_up_key               =  0xAF,    // VK_VOLUME_UP - Volume Up key
        media_next_track_key        =  0xB0,    // VK_MEDIA_NEXT_TRACK - Next Track key
        media_prev_track_key        =  0xB1,    // VK_MEDIA_PREV_TRACK - Previous Track key
        media_stop_key              =  0xB2,    // VK_MEDIA_STOP - Stop Media key
        media_play_pause_key        =  0xB3,    // VK_MEDIA_PLAY_PAUSE - Play/Pause Media key
        launch_mail_key             =  0xB4,    // VK_LAUNCH_MAIL - Start Mail key
        launch_media_select_key     =  0xB5,    // VK_LAUNCH_MEDIA_SELECT - Select Media key
        launch_app1_key             =  0xB6,    // VK_LAUNCH_APP1 - Start Application 1 key
        launch_app2_key             =  0xB7,    // VK_LAUNCH_APP2 - Start Application 2 key
        oem_1_key                   =  0xBA,    // VK_OEM_1 - Can vary by keyboard. US: the ';:' key
        oem_plus_key                =  0xBB,    // VK_OEM_PLUS - For any country/region, the '+' key
        oem_comma_key               =  0xBC,    // VK_OEM_COMMA - For any country/region, the ',' key
        oem_minus_key               =  0xBD,    // VK_OEM_MINUS - For any country/region, the '-' key
        oem_period_key              =  0xBE,    // VK_OEM_PERIOD - For any country/region, the '.' key
        oem_2_key                   =  0xBF,    // VK_OEM_2 - Can vary by keyboard. US: the '/?' key
        oem_3_key                   =  0xC0,    // VK_OEM_3 - Can vary by keyboard. US: the '`~' key
        oem_4_key                   =  0xDB,    // VK_OEM_4 - Can vary by keyboard. US: the '[{' key
        oem_5_key                   =  0xDC,    // VK_OEM_5 - Can vary by keyboard. US: the '\|' key
        oem_6_key                   =  0xDD,    // VK_OEM_6 - Can vary by keyboard. US: the ']}' key
        oem_7_key                   =  0xDE,    // VK_OEM_7 - Can vary by keyboard. US: the 'single-quote/double-quote' key
        oem_8_key                   =  0xDF,    // VK_OEM_8 - Can vary by keyboard.
        oem_102_key                 =  0xE2,    // VK_OEM_102 - US: the <> keys; non-US 102-key keyboard: the \\| key
        process_key                 =  0xE5,    // VK_PROCESSKEY - IME PROCESS key
        packet_key                  =  0xE7,    // VK_PACKET - Used to pass Unicode characters as if they were keystrokes.
        attention_key               =  0xF6,    // VK_ATTN - Attn key
        cr_sel_key                  =  0xF7,    // VK_CRSEL - CrSel key
        ex_sel_key                  =  0xF8,    // VK_EXSEL - ExSel key
        erase_eof_key               =  0xF9,    // VK_EREOF - Erase EOF key
        play_key                    =  0xFA,    // VK_PLAY - Play key
        zoom_key                    =  0xFB,    // VK_ZOOM - Zoom key
        pa1_key                     =  0xFD,    // VK_PA1 - PA1 key
        oem_clear_key               =  0xFE,    // VK_OEM_CLEAR - Clear key
    }; }  // enum + namespace key_codes
}  // namespace fabuluous_support_machinery::keyboard
