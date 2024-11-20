#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

namespace fsm_definitions {

    namespace class_kinds {

        class Polymorphic
        {
        public:
            virtual ~Polymorphic() noexcept {}
        };

    }  // namespace class_kinds
}  // namespace fsm_definitions

namespace fsm {
    inline namespace class_kinds { using namespace fsm_definitions::class_kinds; }
}  // namespace fsm
