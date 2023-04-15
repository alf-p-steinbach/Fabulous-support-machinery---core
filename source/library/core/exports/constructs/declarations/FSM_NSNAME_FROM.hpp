#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

// Example usage:
//
//      FSM_NSNAME_FROM( std, chrono );
//
// Or with $-macros from header <fsm/$-macros.hpp>:
//
//      $nsname_from( std, chrono );


#define FSM_NSNAME_FROM( containing_ns, name ) \
    namespace name = containing_ns::name
