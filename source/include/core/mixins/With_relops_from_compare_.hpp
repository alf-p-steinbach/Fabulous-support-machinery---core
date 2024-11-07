#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/parameter_passing/data_flow_directions.hpp>          // in_

namespace fsm_definitions {
    using   fsm::in_;

    namespace mixins {

        template< class Derived >
        struct With_relops_from_compare_
        {
            friend constexpr auto operator!=( in_<Derived> a, in_<Derived>  b ) noexcept
                -> bool
            { return (compare( a, b ) != 0); }

            friend constexpr auto operator<( in_<Derived> a, in_<Derived>  b ) noexcept
                -> bool
            { return (compare( a, b ) < 0); }

            friend constexpr auto operator<=( in_<Derived> a, in_<Derived>  b ) noexcept
                -> bool
            { return (compare( a, b ) <= 0); }

            friend constexpr auto operator==( in_<Derived> a, in_<Derived>  b ) noexcept
                -> bool
            { return (compare( a, b ) == 0); }

            friend constexpr auto operator>=( in_<Derived> a, in_<Derived>  b ) noexcept
                -> bool
            { return (compare( a, b ) >= 0); }

            friend constexpr auto operator>( in_<Derived> a, in_<Derived>  b ) noexcept
                -> bool
            { return (compare( a, b ) > 0); }
        };

    }  // namespace mixins
}  // namespace fabulous_support_machinery::_definitions

namespace fsm {
    inline namespace mixins { using namespace fsm_definitions::mixins; }
}  // namespace fsm
