#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/constructs/declarations/type_builders.hpp>       // in_

namespace fsm_definitions {
    namespace fsm = fabulous_support_machinery;
    using   fsm::in_;

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

    namespace d = fsm_definitions;
    namespace exports{ using
        d::Relational_operators_mixin_;
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace fsm_definitions::exports; }
