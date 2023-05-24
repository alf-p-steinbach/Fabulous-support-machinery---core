#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/headers/+std-cpp-language.hpp>

#include <fsm/core/headers/constructs/declarations/type_builders.hpp>       // in_

namespace fabulous_support_machinery::_definitions {
    template< class Derived >
    struct Relational_operators_mixin_
    {
        friend auto operator!=( in_<Derived> a, in_<Derived>  b )
            -> bool
        { return (compare( a, b ) != 0); }

        friend auto operator<( in_<Derived> a, in_<Derived>  b )
            -> bool
        { return (compare( a, b ) < 0); }

        friend auto operator<=( in_<Derived> a, in_<Derived>  b )
            -> bool
        { return (compare( a, b ) <= 0); }

        friend auto operator==( in_<Derived> a, in_<Derived>  b )
            -> bool
        { return (compare( a, b ) == 0); }

        friend auto operator>=( in_<Derived> a, in_<Derived>  b )
            -> bool
        { return (compare( a, b ) >= 0); }

        friend auto operator>( in_<Derived> a, in_<Derived>  b )
            -> bool
        { return (compare( a, b ) > 0); }
    };

    namespace d = _definitions;
    namespace exports{ using
        d::Relational_operators_mixin_;
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace _definitions::exports; }
