#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/headers/+std-cpp-language.hpp>

// A more reliable alternative to `[[maybe_unused]]` or `(void) param_name;`.
//
// Unfortunately compiler bugs (g++) and misbehavior (most all) forces “clever”
// code here, and my experience is that compiler behaviors will change so that
// diagnostics are emitted in spite of the cleverness, requiring even more...
//
// Example usage:
//
// TODO: example

#define FSM_NOT_USING( parameter_name ) \
    if( ((void) parameter_name, true) or true ) \
    if( struct parameter_name{} _; ((void)_, true) or true )
