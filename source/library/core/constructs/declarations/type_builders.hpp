#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <type_traits>

namespace fabulous_support_machinery {
    inline namespace type_builders
    {
        // Builders that support template argument deduction:
        template< class T >                 using type_         = T;
        template< class T >                 using const_        = const T;

        template< class T >                 using ref_          = T&;
        template< class T >                 using in_           = ref_<const T>;

        template< const int n, class Item > using array_of_     = Item[n];
    }
}  // namespace fabulous_support_machinery
