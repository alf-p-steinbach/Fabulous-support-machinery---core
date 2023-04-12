#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/basic-types/Size+Index.hpp>   // Size

#include <iterator>     // std::(distance, next)

namespace fabulous_support_machinery::_definitions {
    using   std::distance, std::next;

    template< class tp_C >
    constexpr auto begin_of( tp_C& c )
        -> auto
    { using std::begin; return begin( c ); }

    template< class tp_C >
    constexpr auto end_of( tp_C& c )
        -> auto
    { using std::end; return end( c ); }

    template< class tp_Iterator >
    class Iterator_pair_
    {
        tp_Iterator     m_it_begin;
        tp_Iterator     m_it_end;

    public:
        constexpr Iterator_pair_( const tp_Iterator it_begin, const tp_Iterator it_end ):
            m_it_begin( it_begin ),
            m_it_end( it_end )
        {}

        template< class Collection >
        constexpr Iterator_pair_( Collection& c ):
            m_it_begin( begin_of( c ) ),
            m_it_end( end_of( c ) )
        {}

        constexpr auto begin() const  -> tp_Iterator    { return m_it_begin; }
        constexpr auto end() const    -> tp_Iterator    { return m_it_end; }
        constexpr auto size() const   -> Size           { return distance( m_it_begin, m_it_end ); }
    };

    template< class tp_Iterator >
    constexpr auto all_of( const tp_Iterator it_begin, const tp_Iterator it_end )
        -> Iterator_pair_<tp_Iterator>
    { return {it_begin, it_end}; }

    template< class tp_Collection >
    constexpr auto all_of( tp_Collection&& c )
        -> Iterator_pair_<decltype( begin_of( c ) )>
    { return {c}; }

    template< class tp_Iterator >
    constexpr auto all_except_first_of( const tp_Iterator it_begin, const tp_Iterator it_end )
        -> Iterator_pair_<tp_Iterator>
    { return {next( it_begin ), it_end}; }

    template< class tp_Collection >
    constexpr auto all_except_first_of( tp_Collection&& c )
        -> Iterator_pair_<decltype( begin_of( c ) )>
    { return {next( begin_of( c ) ), end_of( c )}; }

    namespace d = _definitions;
    namespace exports { using
        d::begin_of, d::end_of,
        d::Iterator_pair_,
        d::all_of, d::all_except_first_of;
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace _definitions::exports; }
