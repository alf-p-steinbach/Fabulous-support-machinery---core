#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>
//
// Example:
//
//      FSM_NSNAME_FROM( std, chrono );
//
// Or with $-macros:
//
//      $nsname_from( std, chrono );

#define FSM_NSNAME_FROM( containing_ns, name ) \
    namespace name = containing_ns::name

#ifndef FSM_NO_DOLLAR_MACROS_PLEASE
#   define  $nsname_from    FSM_NSNAME_FROM
#endif
