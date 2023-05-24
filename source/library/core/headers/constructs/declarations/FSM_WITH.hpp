#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/headers/+std-cpp-language.hpp>

// Example usage:
//
//      FSM_WITH( random_point() ) { plot( _.x, _.y ); }
//
// Or with $-macros from header <fsm/$-macros.hpp>:
//
//      $with( random_point() ) { plot( _.x, _.y ); }


#define FSM_WITH( ... ) \
    if( const auto& _ = __VA_ARGS__; ((void)_, true) or true )

#define FSM_WITH_MUTABLE( ... ) \
    if( auto&& _ = __VA_ARGS__; ((void)_, true) or true )
