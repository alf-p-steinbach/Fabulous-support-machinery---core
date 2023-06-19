#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/types/fundamental/byte-types/Byte.hpp>             // Byte
#include <fsm/core/constructs/declarations/type_builders.hpp>   // const_
#include <fsm/core/failure/detecting/FSM_STATIC_ASSERT.hpp>     // FSM_STATIC_ASSERT

namespace fabulous_support_machinery {

    template< class Type >
    constexpr auto byte_cast( const_<Type*> p )
        -> Byte*
    {
        FSM_STATIC_ASSERT( is_byte_<Type> );
        return reinterpret_cast<Byte*>( p );
    }

    template< class Type >
    constexpr auto byte_cast( const_<const Type*> p )
        -> const Byte*
    {
        FSM_STATIC_ASSERT( is_byte_<Type> );
        return reinterpret_cast<const Byte*>( p );
    }

}  // namespace fabulous_support_machinery
