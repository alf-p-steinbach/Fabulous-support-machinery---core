#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <fsm/core/FSM_.hpp>                // FSM_ commenting macro.

namespace fsm_definitions {

    template< class T > using in_ = const T&;
    
    FSM_( "EXPORTS:" ) namespace d = fsm_definitions;  namespace exports {
        using d::in_;
    }  // namespace exports
}  // namespace fsm_definitions

namespace fsm { using namespace fsm_definitions::exports; }
