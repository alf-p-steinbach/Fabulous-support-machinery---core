#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/headers/+std-cpp-language.hpp>

namespace fabulous_support_machinery {
    
    template< class Type >
    constexpr auto the_lvalue( Type& o ) -> Type& { return o; }

    template< class Type >
    constexpr auto the_lvalue( Type&& ) -> Type& = delete;

}  // namespace fabulous_support_machinery
