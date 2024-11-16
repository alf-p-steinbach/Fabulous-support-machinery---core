#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

// A view of a raw array, like C++20 `std::span`
// <url: https://en.cppreference.com/w/cpp/container/span>.

#include <fsm/core/types/fundamental/byte-types/Byte.hpp>                     // is_byte_
#include <fsm/core/types/fundamental/Size+Index.hpp>                          // Size, Index
#include <fsm/core/constructs/declarations/FSM_ENABLE_IF.hpp>           // FSM_ENABLE_IF
#include <fsm/core/constructs/declarations/type_builders.hpp>           // const_
#include <fsm/core/meta-type/type-inspectors.hpp>                       // Bare_
#include <fsm/core/misc/support-for-collections/begin_of+end_of.hpp>    // begin_of, end_of
#include <fsm/core/misc/support-for-collections/Iterator_pair_.hpp>     // Iterator_pair_

#include <iterator>     // std::(next)

namespace fsm_definitions {
    namespace fsm = fabulous_support_machinery;
    using   fsm::is_byte_,
            fsm::Size, fsm::Index,
            fsm::const_,
            fsm::Bare_,
            fsm::begin_of, fsm::end_of,
            fsm::Iterator_pair_;
    using   std::next;

    template< class Item >
    class Span_
    {
        Iterator_pair_<Item*>   m_its;

    public:
        constexpr Span_( const_<Item*> p_start, const_<Item*> p_beyond ):
            m_its( p_start, p_beyond )
        {}

        template< class Other_item, FSM_ENABLE_IF( is_byte_<Item> and is_byte_<Other_item> ) >
        constexpr Span_( in_<Span_<Other_item>> other ):
            Span_(
                reinterpret_cast<Item*>( other.begin() ),
                reinterpret_cast<Item*>( other.end() )
                )
        {}
        
        constexpr auto begin()          -> Item*        { return m_its.begin(); }
        constexpr auto begin() const    -> const Item*  { return m_its.begin(); }
        constexpr auto end()            -> Item*        { return m_its.end(); }
        constexpr auto end() const      -> const Item*  { return m_its.end(); }

        constexpr auto data()           -> Item*        { return m_its.begin(); }
        constexpr auto data() const     -> const Item*  { return m_its.begin(); }
        constexpr auto size() const     -> Size         { return m_its.size(); }
        
        constexpr auto operator[]( const Index i )          -> Item&        { return data()[i]; }
        constexpr auto operator[]( const Index i ) const    -> const Item&  { return data()[i]; }
    };

    // Convenience factory functions with iterator deduction:
    namespace span_factory_functions{
        template< class Item >
        constexpr auto all_of( const_<Item*> p_first, const_<Item*> p_beyond )
            -> Span_<Item>
        { return {p_first, p_beyond}; }

        // Note: customization for a type T needs overloads for both `const T&` and `T&`
        // in order to match better.
        template< class Collection >
        constexpr auto all_of( Collection&& c )
            -> Span_<Bare_<decltype( *begin_of( c ) )>>
        { return {begin_of( c ), end_of( c )}; }

        template< class Item >
        constexpr auto all_except_first_of( const_<Item*> p_first, const_<Item*> p_beyond )
            -> Span_<Item>
        { return {next( p_first ), p_beyond}; }

        template< class Collection >
        constexpr auto all_except_first_of( Collection&& c )
            -> Span_<Bare_<decltype( *begin_of( c ) )>>
        { return {next( begin_of( c ) ), end_of( c )}; }
    }  // namespace span_factory_functions

    namespace d = fsm_definitions;
    namespace exports{
        using
            d::Span_;
        namespace span = d::span_factory_functions;
    }  // namespace exports
        
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery
{
    using namespace fsm_definitions::exports;
    namespace span { using namespace fsm_definitions::exports::span; }
}
