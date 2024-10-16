#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fmt/core.h>
#include <fmt/xchar.h>      // wchar_t support (note: it is/has been borken)

namespace fsm_definitions::fmt_lib {
    using namespace fmt;

#   define FSM_BACKEND_PROVIDES_THE_FORMAT_STRING_TYPE
    constexpr bool api_provides_the_format_string_type = true;
}  // namespace fsm_definitions::fmt_lib
