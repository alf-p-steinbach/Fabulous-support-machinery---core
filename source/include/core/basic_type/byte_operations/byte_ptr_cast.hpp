#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/basic_type/byte_operations/is_byte_.hpp>     // is_byte_
#include <fsm/core/type_builders.hpp>                           // const_

namespace fsm_definitions {
    using   fsm::is_byte_,
            fsm::const_;

    namespace basic_type {
 
        template< class To, class From >
        constexpr auto byte_ptr_cast_( const_<From*> p )
            -> To*
        {
            static_assert( is_byte_<To> );
            static_assert( is_byte_<From> );
            return reinterpret_cast<To*>( p );
        }

    }  // namespace basic_type
}  // namespace fsm_definitions

namespace fsm {
    inline namespace basic_type{ using namespace fsm_definitions::basic_type; }
}  // namespace fsm
