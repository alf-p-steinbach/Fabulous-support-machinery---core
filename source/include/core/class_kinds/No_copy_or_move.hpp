#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <fsm/core/parameter_passing/in_.hpp>

namespace fsm_definitions {
    using   fsm::in_;

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
}  // namespace fsm_definitions

namespace fsm {
    inline namespace class_kinds { using namespace fsm_definitions::class_kinds; }
}  // namespace fsm
