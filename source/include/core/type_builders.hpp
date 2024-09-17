#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <type_traits>

namespace fsm_definitions {
    namespace type_builders
    {
        // Builders that support template argument deduction:
        template< class T >     using type_             = T;
        template< class T >     using movable_value_    = T;
        template< class T >     using const_            = const T;

        template< class T >     using ref_              = T&;
        template< class T >     using in_               = ref_<const T>;

        template< const int n, class Item > using array_of_         = Item[n];
    }
}  // namespace fsm_definitions

namespace fsm {
    inline namespace type_builders {
        using namespace fsm_definitions::type_builders;
    }  // inline namespace type_builders
}  // namespace fsm
