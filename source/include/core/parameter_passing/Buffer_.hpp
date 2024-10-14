#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <utility>

namespace fsm_definitions {
    using   std::move;        // <utility>

    namespace parameter_passing {
        template< class Container >
        class Buffer_
        {
            Container   m_object;
            
        public:
            Buffer_( Container&& o ): m_object( move( o ) ) {}
            auto rvref() -> Container&& { return move( m_object ); }
        };
    }  // namespace parameter_passing
}  // namespace fsm_definitions

namespace fsm {
    inline namespace parameter_passing { using namespace fsm_definitions::parameter_passing; }
}  // namespace fsm
