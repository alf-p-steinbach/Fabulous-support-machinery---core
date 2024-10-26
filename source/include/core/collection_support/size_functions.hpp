#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/type_builders.hpp>                       // in_
#include <fsm/core/basic_type/names/Index-and-Size.hpp>     // Index, Size (as ptrdiff_t)

#include    <iterator>      // std::(distance, size)

namespace fsm_definitions {
    using   fsm::in_,                   // type_builders.hpp
            fsm::Size;                  // basic_type/names/Index-and-size.hpp
    using   std::size_t,                // <cstddef>
            std::distance, std::size;   // <iterator>

    namespace collection_support {
        template< class Container >
        constexpr auto is_empty( in_<Container> c ) noexcept
            -> bool
        { return c.empty(); }

        template< class Item, Size n >
        constexpr auto is_empty( in_<Item[n]> ) noexcept
            -> bool
        {
            static_assert( n > 0 );
            return false;
        }

        template< class Container >
        constexpr auto size_of( in_<Container> c ) noexcept
            -> Size
        { return static_cast<Size>( size( c ) ); }          // Like C++20 std::ssize.

        template< class Container >
        constexpr auto usize_of( in_<Container> c ) noexcept
            -> size_t
        { return size( c ); }

        template< class Container >                         // Use with care -- no range checking.
        constexpr auto int_size_of( in_<Container> c ) noexcept
            -> int
        { return static_cast<int>( size_of( c ) ); }

        template< class Container >                         // Use with care -- no range checking.
        constexpr auto int_capacity_of( in_<Container> c ) noexcept
            -> int
        { return static_cast<int>( c.capacity() ); }

        // Placed here because it belongs with the `int_size_of` function, even if not about collection.
        template< class It >                                // Use with care -- no range checking.
        constexpr auto int_distance_from_to( const It a, const It b ) noexcept
            -> int
        { return static_cast<int>( distance( a, b ) ); }
    }  // namespace collection_support
}  // namespace fsm_definitions

namespace fsm {
    inline namespace collection_support{ using namespace fsm_definitions::collection_support; }
}  // namespace fsm
