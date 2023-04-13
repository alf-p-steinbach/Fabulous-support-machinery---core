#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

// Mostly for use in range based `for` loops, e.g.
//
//      for( in_<T>: its::all_of( p, p + size ) ) { ...
//      for( in_<T>: its::all_x_first_of( vec ) ) { ...

#include <fsm/core/exports/basic-types/Size+Index.hpp>                      // Size
#include <fsm/core/exports/support-for-collections/begin_of+end_of.hpp>     // begin_of, end_of

#include <iterator>     // std::(distance, next)

namespace fabulous_support_machinery::_definitions {
    using   std::distance, std::next;

    template< class Iterator >
    class Iterator_pair_
    {
        Iterator    m_it_begin;
        Iterator    m_it_end;

    public:
        constexpr Iterator_pair_( const Iterator it_begin, const Iterator it_end ):
            m_it_begin( it_begin ),
            m_it_end( it_end )
        {}

        template< class Collection >
        constexpr Iterator_pair_( Collection& c ):
            m_it_begin( begin_of( c ) ),
            m_it_end( end_of( c ) )
        {}

        constexpr auto begin() const    -> Iterator     { return m_it_begin; }
        constexpr auto end() const      -> Iterator     { return m_it_end; }
        constexpr auto size() const     -> Size         { return distance( m_it_begin, m_it_end ); }
    };

    // Convenience factory functions with iterator deduction:
    namespace its {
        // `all`:
        template< class Iterator >
        constexpr auto all_of( const Iterator it_begin, const Iterator it_end )
            -> Iterator_pair_<Iterator>
        { return {it_begin, it_end}; }

        template< class Collection >
        constexpr auto all_of( Collection&& c )
            -> Iterator_pair_<decltype( begin_of( c ) )>
        { return {c}; }

        // `all_x_first_of`:
        template< class Iterator >
        constexpr auto all_x_first_of( const Iterator it_begin, const Iterator it_end )
            -> Iterator_pair_<Iterator>
        { return {next( it_begin ), it_end}; }

        template< class Collection >
        constexpr auto all_x_first_of( Collection&& c )
            -> Iterator_pair_<decltype( begin_of( c ) )>
        { return {next( begin_of( c ) ), end_of( c )}; }
    }  // namespace its

    namespace d = _definitions;
    namespace exports { using
        d::Iterator_pair_;
        namespace its = d::its;     // all_of, all_x_first_of
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace _definitions::exports; }
