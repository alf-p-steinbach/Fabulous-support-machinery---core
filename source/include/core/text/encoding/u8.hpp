#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <type_traits>

namespace fsm_definitions {

    // Builders that support template argument deduction:
    namespace text::u8
    {
        
    }
}  // namespace fsm_definitions

namespace fsm {
    inline namespace text { using namespace fsm_definitions::text; }
}  // namespace fsm
