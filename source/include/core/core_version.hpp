#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <fsm/core/FSM_.hpp>                // FSM_ commenting macro.
#include <fsm/core/Version.hpp>

namespace fsm_definitions {

    inline const auto core_version   = Version{ "FSM core sub-library version 1.0" };

    FSM_( "EXPORTS:" ) namespace d = fsm_definitions;  namespace exports {
        using   d::core_version;
    }  // namespace exports
}  // namespace fsm_definitions

namespace fsm { using namespace fsm_definitions::exports; }
