#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

namespace fsm_definitions {
    namespace collections{

        template< class Collection >
        void remove_buffer_of( Collection& c )
        {
            if( c.capacity() ) {
                Collection().swap( c );
                // Size is 0, capacity is minimum.
            }
        }
    }  // namespace collections
}  // namespace fsm_definitions

namespace fsm {
    inline namespace collections { using namespace fsm_definitions::collections; }
}  // namespace fsm
