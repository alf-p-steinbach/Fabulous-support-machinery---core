#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <fsm/core/FSM_.hpp>                // FSM_ commenting macro.
#include <utility>

namespace fsm_definitions {
    using   std::enable_if_t;       // <utility>

    template< bool condition >
    using Enable_if_ = enable_if_t<condition, bool>;
    
    FSM_( "EXPORTS:" ) namespace d = fsm_definitions;  namespace exports {
        using   d::Enable_if_;
    }  // namespace exports
}  // namespace fsm_definitions

namespace fsm{ using namespace fsm_definitions::exports; };
