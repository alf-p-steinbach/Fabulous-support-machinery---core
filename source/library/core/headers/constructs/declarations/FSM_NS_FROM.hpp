#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/headers/+std-cpp-language.hpp>

// Example usage:
//
//      FSM_NS_FROM( std, chrono );
//
// Or with $-macros from header <fsm/$-macros.hpp>:
//
//      $ns_from( std, chrono );


#define FSM_NS_FROM( containing_ns, name ) \
    namespace name = containing_ns::name
