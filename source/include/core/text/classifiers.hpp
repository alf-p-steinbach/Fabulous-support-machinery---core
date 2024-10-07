#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

namespace fsm_definitions {
    namespace text {

        // Intentionally not checking \f, \r and \v: they don’t usually occur in practice.
        constexpr auto is_ascii_whitespace( const char ch )
            -> bool
        { return (ch == ' ' or ch == '\n' or ch == '\t'); }

    }  // namespace text
}  // namespace fsm_definitions

namespace fsm {
    inline namespace text{ using namespace fsm_definitions::text; }
}  // namespace fsm
