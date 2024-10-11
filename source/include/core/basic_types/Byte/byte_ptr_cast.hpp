#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <fsm/core/basic_types/Byte/is_byte_.hpp>       // is_byte_
#include <fsm/core/type_builders.hpp>                   // const_

namespace fsm_definitions {
    using   fsm::is_byte_,
            fsm::const_;

    namespace basic_types {
 
        template< class To, class From >
        constexpr auto byte_ptr_cast_( const_<From*> p )
            -> To*
        {
            static_assert( is_byte_<To> );
            static_assert( is_byte_<From> );
            return reinterpret_cast<To*>( p );
        }

    }  // namespace basic_types
}  // namespace fsm_definitions

namespace fsm {
    inline namespace basic_types{ using namespace fsm_definitions::basic_types; }
}  // namespace fsm
