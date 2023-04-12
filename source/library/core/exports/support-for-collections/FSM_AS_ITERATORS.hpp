#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

// Example usage:
//
//      sort( FSM_AS_ITERATORS( items ) );
//
// Or with $-macros from header <fsm/$-macros.hpp>:
//
//      sort( $as_iterators( items ) );


#include <iterator>

#define FSM_AS_ITERATORS( collection ) \
    std::begin( fabulous_support_machinery::_definitions::lvalue( collection ) ), \
    std::end( collection )

namespace fabulous_support_machinery::_definitions {
    
    template< class Type >
    constexpr auto lvalue( Type& o ) -> Type& { return o; }

}  // namespace fabulous_support_machinery::_definitions
