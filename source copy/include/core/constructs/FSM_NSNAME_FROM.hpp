#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>
//
// Example:
//
//      $nsname_from( std, chrono );
//
// Or with uppercase macros:
//
//      FSM_NSNAME_FROM( std, chrono );

#define FSM_NSNAME_FROM( containing_ns, name ) \
    namespace name = containing_ns::name

#define $nsname_from    FSM_NSNAME_FROM
