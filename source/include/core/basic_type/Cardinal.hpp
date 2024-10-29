#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/wrapped/c_lib/assert.hpp>            // assert
#include <fsm/core/wrapped/c_lib/limits.hpp>            // INT_MAX

namespace fsm_definitions {
    namespace basic_type {

        // The notion of a non-negative integer à la Modula-2:
        enum Cardinal: int {};                  // `Cardinal` converts implicitly to `int`.

        constexpr auto as_cardinal( const int x ) noexcept
            -> Cardinal
        {
            assert( x >= 0 );
            return Cardinal( x );
        }

        constexpr auto cardinal_1 = Cardinal( 1 );

        constexpr auto operator+( const Cardinal x ) noexcept -> Cardinal { return x; }

        constexpr auto operator+( const Cardinal a, const Cardinal b ) noexcept
            -> Cardinal
        { return Cardinal( a + b ); }

        constexpr auto operator+=( Cardinal& a, const Cardinal b ) noexcept
            -> Cardinal&
        { return (a = a + b); }

        constexpr auto operator-( const Cardinal ) -> Cardinal = delete;

        constexpr auto operator-( const Cardinal a, const Cardinal b ) noexcept
            -> Cardinal
        {
            assert( a >= b );
            return Cardinal( a - b );
        }

        constexpr auto operator-=( Cardinal& a, const Cardinal b ) noexcept
            -> Cardinal&
        { return (a = a - b); }

        constexpr auto operator*( const Cardinal a, const Cardinal b ) noexcept
            -> Cardinal
        { return Cardinal( a * b ); }

        constexpr auto operator*=( Cardinal& a, const Cardinal b ) noexcept
            -> Cardinal&
        { return (a = a * b); }

        constexpr auto operator/( const Cardinal a, const Cardinal b ) noexcept
            -> Cardinal
        {
            assert( b != 0 );
            return Cardinal( a / b );
        }
        constexpr auto operator/=( Cardinal& a, const Cardinal b ) noexcept
            -> Cardinal&
        { return (a = a / b); }

        constexpr auto succ( const Cardinal x ) noexcept -> Cardinal { return x + cardinal_1; }
        constexpr auto pred( const Cardinal x ) noexcept -> Cardinal { return x - cardinal_1; }

        // When `limit` is guaranteed not negative and `x` just may be negative, instead of
        //
        //      0 < x and x < limit
        //
        // one can use
        //
        //      in_range_zero_up_to( limit, x )
        //
        // Probably a modern compiler will optimize to this anyway. But may be more clear.
        //
        constexpr auto in_range_zero_up_to( const Cardinal limit, const int x ) noexcept
            -> bool
        { return (unsigned( x ) < unsigned( limit )); }
    }  // namespace basic_type
}  // namespace fsm_definitions

namespace fsm {
    inline namespace basic_type{ using namespace fsm_definitions::basic_type; }
}  // namespace fsm
