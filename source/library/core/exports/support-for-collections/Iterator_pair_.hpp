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

    // TODO: derive from `std::pair`
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

        constexpr auto begin() const    -> Iterator     { return m_it_begin; }
        constexpr auto end() const      -> Iterator     { return m_it_end; }
        constexpr auto size() const     -> Size         { return distance( m_it_begin, m_it_end ); }
    };

    // // Convenience factory functions with iterator deduction:
    // namespace iterator_pair_factory_functions{
        // template< class Iterator >
        // constexpr auto all_of( const Iterator it_begin, const Iterator it_end )
            // -> Iterator_pair_<Iterator>
        // { return {it_begin, it_end}; }

        // // This is the primary general function. Overloads defined in separate headers
        // // for container wrappers, e.g. stack and queue. Note: customization for a type
        // // T needs overloads for both `const T&` and `T&` in order to match better.
        // template< class Collection >
        // constexpr auto all_of( Collection&& c )
            // -> Iterator_pair_<decltype( begin_of( c ) )>
        // { return {begin_of( c ), end_of( c )}; }

        // template< class Iterator >
        // constexpr auto all_except_first_of( const Iterator it_begin, const Iterator it_end )
            // -> Iterator_pair_<Iterator>
        // { return {next( it_begin ), it_end}; }

        // template< class Collection >
        // constexpr auto all_except_first_of( Collection&& c )
            // -> Iterator_pair_<decltype( begin_of( c ) )>
        // { return {next( begin_of( c ) ), end_of( c )}; }
    // }  // namespace iterator_pair_factory_functions

    namespace d = _definitions;
    namespace exports{ using
        d::Iterator_pair_;
        // using namespace d::iterator_pair_factory_functions;
    }  // namespace exports
        
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace _definitions::exports; }
