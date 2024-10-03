#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <fsm/core/class_kinds/No_copy_or_move.hpp>     // No_copy_or_move
#include <fsm/core/platform/os_id_macros.hpp>           // FSM_OS_...

#include <cstdint>

namespace fsm_definitions {
    using   fsm::No_copy_or_move;
    using   std::uint32_t;          // <cstdint>

    #ifdef FSM_OS_IS_WINDOWS
        namespace windows_impl {
            extern auto console_codepage() -> int;
            extern void set_console_codepage( int cp );
            constexpr int codepage_utf8 = 65001;                // MS `CP_UTF8`
            
            extern auto console_mode() -> uint32_t;
            extern void set_console_mode( uint32_t new_mode );
            constexpr uint32_t enable_console_ansi_escapes = 4; // MS `ENABLE_VIRTUAL_TERMINAL_PROCESSING`
        }  // namespace windows_impl
        
        using namespace windows_impl;
    #endif

    namespace stream_io {
        #ifdef FSM_OS_IS_WINDOWS
            class Console_fix: No_copy_or_move
            {
                int         m_original_cp;
                uint32_t    m_original_mode;
              
            public:
                ~Console_fix()
                {
                    set_console_codepage( m_original_cp );
                    set_console_mode( m_original_cp );
                }

                Console_fix() noexcept:
                    m_original_cp( console_codepage() ),
                    m_original_mode( console_mode() )
                {
                    set_console_mode( m_original_mode | enable_console_ansi_escapes );
                    set_console_codepage( codepage_utf8 );
                }
            };
        #else
            struct Console_fix: No_copy_or_move
            {
                ~Console_fix()  {}
                Console_fix()   {}
            };
        #endif
    }  // namespace stream_io
}  // namespace fsm_definitions

namespace fsm {
    inline namespace stream_io { using namespace fsm_definitions::stream_io; }
}  // namespace fsm
