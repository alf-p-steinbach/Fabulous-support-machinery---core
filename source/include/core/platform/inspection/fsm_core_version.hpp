#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <string>

namespace fsm_definitions {
    using std::string;

    namespace platform {
        inline const auto fsm_core_version  = string( "FSM core sub-library version 1.0" );
    }  // namespace platform
}  // namespace fsm_definitions

namespace fsm {
    inline namespace platform{ using namespace fsm_definitions::platform; }
}  // namespace fsm
