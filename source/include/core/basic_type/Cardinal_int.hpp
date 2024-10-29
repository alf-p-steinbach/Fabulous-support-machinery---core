#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/wrapped/c_lib/assert.hpp>            // assert
#include <fsm/core/wrapped/c_lib/limits.hpp>            // INT_MAX

namespace fsm_definitions {
    namespace basic_type {

        // The notion of a non-negative integer à la Modula-2:
        enum Cardinal_int: int {};              // `Cardinal_int` converts implicitly to `int`.

        using Ꜿint = Cardinal_int;              // Latin capital letter reversed c with dot, U+A73E.

        constexpr auto as_cardinal( const int x ) noexcept
            -> Ꜿint
        {
            assert( x >= 0 );
            return Ꜿint( x );
        }

        constexpr auto cardinal_1   = Ꜿint( 1 );
        constexpr auto Ꜿ1           = cardinal_1;

        constexpr auto operator+( const Ꜿint x ) noexcept -> Ꜿint { return x; }

        constexpr auto operator+( const Ꜿint a, const Ꜿint b ) noexcept
            -> Ꜿint
        { return Ꜿint( a + b ); }

        constexpr auto operator+=( Ꜿint& a, const Ꜿint b ) noexcept
            -> Ꜿint&
        { return (a = a + b); }

        constexpr auto operator-( const Ꜿint ) -> Ꜿint = delete;

        constexpr auto operator-( const Ꜿint a, const Ꜿint b ) noexcept
            -> Ꜿint
        {
            assert( a >= b );
            return Ꜿint( a - b );
        }

        constexpr auto operator-=( Ꜿint& a, const Ꜿint b ) noexcept
            -> Ꜿint&
        { return (a = a - b); }

        constexpr auto operator*( const Ꜿint a, const Ꜿint b ) noexcept
            -> Ꜿint
        { return Ꜿint( a * b ); }

        constexpr auto operator*=( Ꜿint& a, const Ꜿint b ) noexcept
            -> Ꜿint&
        { return (a = a * b); }

        constexpr auto operator/( const Ꜿint a, const Ꜿint b ) noexcept
            -> Ꜿint
        {
            assert( b != 0 );
            return Ꜿint( a / b );
        }
        constexpr auto operator/=( Ꜿint& a, const Ꜿint b ) noexcept
            -> Ꜿint&
        { return (a = a / b); }

        constexpr auto succ( const Ꜿint x ) noexcept -> Ꜿint { return x + cardinal_1; }
        constexpr auto pred( const Ꜿint x ) noexcept -> Ꜿint { return x - cardinal_1; }

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
        constexpr auto in_range_zero_up_to( const Ꜿint limit, const int x ) noexcept
            -> bool
        { return (unsigned( x ) < unsigned( limit )); }
    }  // namespace basic_type
}  // namespace fsm_definitions

namespace fsm {
    inline namespace basic_type{ using namespace fsm_definitions::basic_type; }
}  // namespace fsm
