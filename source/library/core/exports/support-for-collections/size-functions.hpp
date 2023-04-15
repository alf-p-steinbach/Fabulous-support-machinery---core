#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/failure/detecting/FSM_STATIC_ASSERT.hpp>    // FSM_STATIC_ASSERT
#include <fsm/core/exports/constructs/type_builders.hpp>                         // in_
#include <fsm/core/exports/basic-types/Size+Index.hpp>                // Size (as ptrdiff_t)

#include    <iterator>      // std::(distance, size)

namespace fabulous_support_machinery {

    template< class Container >
    constexpr auto is_empty( in_<Container> c ) noexcept
        -> bool
    { return c.empty(); }

    template< class Item, Size n >
    constexpr auto is_empty( in_<Item[n]> ) noexcept
        -> bool
    {
        FSM_STATIC_ASSERT( n > 0 );
        return false;
    }

    template< class Container >
    constexpr auto size_of( in_<Container> c ) noexcept
        -> Size
    { return static_cast<Size>( std::size( c ) ); }     // Like C++20 std::ssize.

    template< class Container >
    constexpr auto unsigned_size_of( in_<Container> c ) noexcept
        -> Unsigned_size
    { return std::size( c ); }

    template< class Container >                         // Use with care -- no range checking.
    constexpr auto int_size_of( in_<Container> c ) noexcept
        -> int
    { return static_cast<int>( size_of( c ) ); }

    template< class Container >                         // Use with care -- no range checking.
    constexpr auto int_capacity_of( in_<Container> c ) noexcept
        -> int
    { return static_cast<int>( c.capacity() ); }

    // Placed here because it belongs with the `int_size` function, even if not about collection.
    template< class It >                                // Use with care -- no range checking.
    constexpr auto int_distance_of( const It a, const It b ) noexcept
        -> int
    { return static_cast<int>( std::distance( a, b ) ); }

}  // namespace fabulous_support_machinery::_definitions;
