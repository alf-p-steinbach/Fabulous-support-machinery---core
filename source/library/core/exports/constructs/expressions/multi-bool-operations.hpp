#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/declarations/type_builders.hpp>       // in_

#include <utility>

namespace fabulous_support_machinery::_definitions {
    using   std::forward;       // <utility>
       
    // AND
    template< class... Args >
    constexpr auto all_of( const Args&... args )
        -> bool
    { return (args and ...); }

    template< class Unary_predicate, class... Args >
    constexpr auto all( in_<Unary_predicate> p, const Args&... args )
        -> bool
    { return all_of( p( forward<Args>( args ) )... ); }

    // OR
    template< class... Args >
    constexpr auto any_of( const Args&... args )
        -> bool
    { return (args or ...); }

    template< class Unary_predicate, class... Args >
    constexpr auto any( in_<Unary_predicate> p, const Args&... args )
        -> bool
    { return any_of( p( forward<Args>( args ) )... ); }

    // XOR.
    template< class... Args >
    constexpr auto exactly_one_of( const Args&... args )
        -> bool
    { return ((!!args + ...) == 1); }

    template< class Unary_predicate, class... Args >
    constexpr auto exactly_one( in_<Unary_predicate> p, const Args&... args )
        -> bool
    { return exactly_one_of( p( forward<Args>( args ) )... ); }

    namespace d = _definitions;
    namespace exports { using
        d::all_of,
        d::all,
        d::any_of,
        d::any,
        d::exactly_one_of,
        d::exactly_one;
    }
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery{
    using namespace _definitions::exports;

    // Not a simple equate because may need to be an extension of earlier declared namespace.
    namespace boolean_ops {
        using namespace _definitions::exports;
    }  // namespace boolean_ops

}  // namespace fabulous_support_machinery
