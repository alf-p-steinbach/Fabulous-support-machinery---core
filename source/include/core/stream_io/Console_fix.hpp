#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/basic_type/Natural_int.hpp>                     // Nat
#include <fsm/core/class_kinds/No_copy_or_move.hpp>                 // No_copy_or_move
#include <fsm/core/platform/inspection/os_id_macros.hpp>            // FSM_OS_...

#include <cstdint>

namespace fsm_definitions {
    using   fsm::Nat,                      // basic_type/Natural_int.hpp
            fsm::No_copy_or_move;           // class_kinds/No_copy_or_move.hpp

    using   std::uint32_t;          // <cstdint>

    #ifdef FSM_OS_IS_WINDOWS
        namespace windows_impl {
            extern auto console_codepage() -> Nat;
            extern void set_console_codepage( Nat cp );
            constexpr Nat codepage_utf8 = 65001;                // MS `CP_UTF8`
            
            extern auto console_mode() -> uint32_t;
            extern void set_console_mode( uint32_t new_mode );
            constexpr uint32_t enable_console_ansi_escapes = 4; // MS `ENABLE_VIRTUAL_TERMINAL_PROCESSING`

            class Console_fix: No_copy_or_move
            {
                Nat        m_original_cp;
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
        }  // namespace windows_impl
    #endif

    namespace stream_io {
        #ifdef FSM_OS_IS_WINDOWS
            struct Console_fix: windows_impl::Console_fix {};
        #else
            struct Console_fix: No_copy_or_move {};
        #endif
    }  // namespace stream_io
}  // namespace fsm_definitions

namespace fsm {
    inline namespace stream_io { using namespace fsm_definitions::stream_io; }
}  // namespace fsm
