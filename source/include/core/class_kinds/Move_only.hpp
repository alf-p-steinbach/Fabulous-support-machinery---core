#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <fsm/core/FSM_.hpp>                // FSM_ commenting macro.

#include <fsm/core/parameter_passing/in_.hpp>

namespace fsm_definitions {

    namespace class_kinds {
        class Move_only
        {
            using Self = Move_only;
            Move_only( in_<Self> ) = delete;
            auto operator=( in_<Self> ) -> Self& = delete;
            
        public:
            Move_only() noexcept {}
            Move_only( Self&& ) noexcept {}
            auto operator=( Self&& ) noexcept -> Self& { return *this; }
        };
    }  // namespace class_kinds

    FSM_( "EXPORTS:" ) namespace d = fsm_definitions;  namespace exports {
        namespace class_kinds = d::class_kinds;
    }  // namespace exports
}  // namespace fsm_definitions

namespace fsm { using namespace fsm_definitions::exports; }
