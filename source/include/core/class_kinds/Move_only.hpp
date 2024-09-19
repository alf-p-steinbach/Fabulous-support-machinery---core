#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <fsm/core/parameter_passing/in_.hpp>

namespace fsm_definitions {
    using   fsm::in_;

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
}  // namespace fsm_definitions

namespace fsm {
    inline namespace class_kinds { using namespace fsm_definitions::class_kinds; }
}  // namespace fsm
