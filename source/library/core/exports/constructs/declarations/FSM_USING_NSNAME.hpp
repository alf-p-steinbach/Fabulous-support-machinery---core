#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

// Example usage:
//
//      FSM_USING_NSNAME( std, chrono );
//
// Or with $-macros from header <fsm/$-macros.hpp>:
//
//      $using_nsname( std, chrono );


#define FSM_USING_NSNAME( containing_ns, name ) \
    namespace name = containing_ns::name
