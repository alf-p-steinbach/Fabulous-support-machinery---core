#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <fsm/core/FSM_.hpp>                // FSM_ commenting macro.

#include <fsm/core/parameter_passing/in_.hpp>

namespace fsm_definitions {

    namespace class_kinds {
        class No_copy_or_move
        {
            using Self = No_copy_or_move;
            No_copy_or_move( in_<Self> ) = delete;
            auto operator=( in_<Self> ) -> Self& = delete;
            
        public:
            No_copy_or_move() noexcept {}
        };
    }  // namespace class_kinds

    FSM_( "EXPORTS:" ) namespace d = fsm_definitions;  namespace exports {
        namespace class_kinds = d::class_kinds;
    }  // namespace exports
}  // namespace fsm_definitions

namespace fsm { using namespace fsm_definitions::exports; }
