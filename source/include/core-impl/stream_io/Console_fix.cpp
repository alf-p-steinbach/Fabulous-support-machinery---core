#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/stream_io/Console_fix.hpp>

namespace fsm_definitions::windows_impl {
    extern auto console_codepage() -> int;
    extern void set_console_codepage( int cp );
    
    extern auto console_mode() -> uint32_t;
    extern void set_console_mode( uint32_t new_mode );
}  // namespace fsm_definitions::windows_impl
