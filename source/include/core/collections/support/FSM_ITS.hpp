#pragma once // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

// “ITS” is either the posessive pronoun or short for “iterators”, whatever fits best.
//
// Example usage:
//
//     sort( $its( items ) );
//
// Or with classic uppercase prefixed macro name
//
//     sort( FSM_ITS( items ) );

#define FSM_ITS( collection )                   \
    fsm_definitions::begin_of( collection ), fsm_definitions::end_of( collection )

#ifndef FSM_NO_DOLLAR_MACROS_PLEASE
#   define $its     FSM_ITS
#endif

#include <iterator>         // std::(begin, end)

// TODO: move to separate header and export:
namespace fsm_definitions {

    template< class Collection >
    auto begin_of( Collection& c )
        -> auto
    { using std::begin; return begin( c ); }

    template< class Collection > auto begin_of( Collection&& ) -> auto = delete;

    template< class Collection >
    auto end_of( Collection& c )
        -> auto
    { using std::end; return end( c ); }

    template< class Collection > auto end_of( Collection&& ) -> auto = delete;

}  // namespace fsm_definitions
