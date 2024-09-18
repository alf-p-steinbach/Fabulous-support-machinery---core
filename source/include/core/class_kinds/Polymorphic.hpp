#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <fsm/core/FSM_.hpp>                            // FSM_ commenting macro.
#include <fsm/core/constructs/FSM_NSNAME_FROM.hpp>      // FSM_NSNAME_FROM

namespace fsm_definitions {

    namespace class_kinds {
        class Polymorphic
        {
        public:
            virtual ~Polymorphic() noexcept {}
        };
    }  // namespace class_kinds

    FSM_( "EXPORTS:" ) namespace d = fsm_definitions;  namespace exports {
        FSM_NSNAME_FROM( d, class_kinds );
    }  // namespace exports
}  // namespace fsm_definitions

namespace fsm { using namespace fsm_definitions::exports; }
