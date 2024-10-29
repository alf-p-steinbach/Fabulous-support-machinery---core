#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/wrapped/c_lib/limits.hpp>

namespace fsm_definitions {
    namespace basic_type {

        using Byte = unsigned char;
        constexpr int bits_per_byte = CHAR_BIT;     // From <limits.h>

    }  // namespace basic_type
}  // namespace fsm_definitions

namespace fsm {
    inline namespace basic_type{ using namespace fsm_definitions::basic_type; }
}  // namespace fsm
