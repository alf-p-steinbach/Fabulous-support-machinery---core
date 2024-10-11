#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

namespace fsm_definitions {
    namespace basic_types {

        using C_str = const char*;

    }  // namespace basic_types
}  // namespace fsm_definitions

namespace fsm {
    inline namespace basic_types{ using namespace fsm_definitions::basic_types; }
}  // namespace fsm
