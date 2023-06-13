#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

// “ITS” is either the posessive pronoun or short for “iterators”, whatever fits best.
//
// Example usage:
//
//      sort( FSM_ITS_RANGE( items ) );
//
// Or with $-macros from header <fsm/$-macros.hpp>:
//
//      sort( $its_range( items ) );


#include <fsm/core/misc/support-for-collections/begin_of+end_of.hpp>
#include <fsm/core/misc/support-for-macros/the_lvalue.hpp>

#define FSM_ITS_RANGE( collection ) \
    fabulous_support_machinery::begin_of( fabulous_support_machinery::the_lvalue( collection ) ), \
    fabulous_support_machinery::end_of( collection )
