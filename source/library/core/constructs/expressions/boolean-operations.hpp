#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

// Mostly for use in template programming, e.g. FSM_ENABLE_IF expressions.

#include <fsm/core/constructs/declarations/type_builders.hpp>       // in_

#include <utility>

namespace fsm_definitions::boolean_ops {
    namespace fsm = fabulous_support_machinery;
    using   fsm::in_;
    using   std::forward;       // <utility>

    // Implication. True if the values are not inconsistent with (premise implies conclusion).
    //
    template< class Premise, class Conclusion >
    constexpr auto implication_permits( in_<Premise> premise, in_<Conclusion> conclusion )
        -> bool
    { return (!!premise <= !!conclusion); }

    // The “either-or” XOR generalization.
    //
    template< class... Args >
    constexpr auto exactly_one_of( const Args&... args )
        -> bool
    { return ((!!args + ...) == 1); }

    template< class Unary_predicate, class... Args >
    constexpr auto exactly_one( in_<Unary_predicate> p, const Args&... args )
        -> bool
    { return exactly_one_of( !!p( forward<Args>( args ) )... ); }

    // Simple OR, for completeness (inferior to built-in op's short-circuit evaluation).
    //
    template< class... Args >
    constexpr auto any_of( const Args&... args )
        -> bool
    { return (!!args or ...); }

    template< class Unary_predicate, class... Args >
    constexpr auto any( in_<Unary_predicate> p, const Args&... args )
        -> bool
    { return (!!p( forward<Args>( args ) ) or ... ); }

    // NOR.
    //
    template< class... Args >
    constexpr auto none_of( const Args&... args )
        -> bool
    { return not (!!args or ...); }

    template< class Unary_predicate, class... Args >
    constexpr auto none( in_<Unary_predicate> p, const Args&... args )
        -> bool
    { return not (!!p( forward<Args>( args ) ) or ...); }

    // NAND.
    //
    template< class... Args >
    constexpr auto not_all_of( const Args&... args )
        -> bool
    { return not (!!args and ...); }

    template< class Unary_predicate, class... Args >
    constexpr auto not_all( in_<Unary_predicate> p, const Args&... args )
        -> bool
    { return not (!!p( forward<Args>( args ) ) and ...); }

    // Simple AND, for completeness (inferior to built-in op's short-circuit evaluation).
    //
    template< class... Args >
    constexpr auto all_of( const Args&... args )
        -> bool
    { return (!!args and ...); }

    template< class Unary_predicate, class... Args >
    constexpr auto all( in_<Unary_predicate> p, const Args&... args )
        -> bool
    { return (!!p( forward<Args>( args ) ) and ... ); }

    namespace x = boolean_ops;
    namespace exports { using
        x::implication_permits,     // A implies B
        x::exactly_one_of,          // either A or B
        x::exactly_one,             // either f(A) or f(B)
        x::any_of,                  // A or B
        x::any,                     // f(A) or f(B)
        x::none_of,                 // not( A or B )
        x::none,                    // not( f(A) or f(B) )
        x::not_all_of,              // not( A and B )
        x::not_all,                 // not( f(A) and f(B) )
        x::all_of,                  // A and B
        x::all;                     // f(A) and f(B)
    }
}  // namespace fsm_definitions::boolean_ops

namespace fabulous_support_machinery{
    using namespace fsm_definitions::boolean_ops::exports;

    // Not a simple equate because may need to be an extension of earlier declared namespace.
    namespace boolean_ops{
        using namespace fsm_definitions::boolean_ops::exports;
    }  // namespace boolean_ops
}  // namespace fabulous_support_machinery
