#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/headers/+std-cpp-language.hpp>

// Example usage:
//
//      FSM_STATIC_ASSERT( std::numeric_limits<double>::is_iec559 or !"IEEE-754 is required" );
//
// Or with $-macros from header <fsm/$-macros.hpp>:
//
//      $static_assert( std::numeric_limits<double>::is_iec559 or !"IEEE-754 is required" );


#define FSM_STATIC_ASSERT_IMPL( condition ) \
    static_assert( condition, #condition )

#define FSM_STATIC_ASSERT( ... ) \
    FSM_STATIC_ASSERT_IMPL(( __VA_ARGS__ ))
