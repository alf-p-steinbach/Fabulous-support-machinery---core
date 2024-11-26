#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <type_traits>

namespace fsm_definitions {

    // Builders that support template argument deduction:
    namespace type_builders
    {
        template< class T >     using type_             = T;
        template< class T >     using const_            = const T;
        template< class T >     using ref_              = T&;

        template< const int n, class Item > using array_of_         = Item[n];
    }

}  // namespace fsm_definitions

namespace fsm {
    inline namespace type_builders { using namespace fsm_definitions::type_builders; }
}  // namespace fsm
