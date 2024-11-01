#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/wrapped/c_lib/assert.hpp>            // assert
#include <fsm/core/wrapped/c_lib/limits.hpp>            // INT_MAX

namespace tag {
    using Unchecked = struct Unchecked_struct*;
}  // namesapace tag

namespace fsm_definitions {

    namespace basic_type {

        // TODO: numeric_limits specialization
        // TODO: relational operators

        // The notion of a non-negative integer à la Modula-2:
        class Cardinal_int
        {
            int     m_value     = 0;

        public:
            static constexpr auto unchecked = tag::Unchecked();

            constexpr Cardinal_int( tag::Unchecked, const int value ):
                m_value( value )
            {}

            constexpr Cardinal_int(): m_value( 0 ) {}   // Supports e.g. `Ꜿint x = {};`.

            constexpr explicit Cardinal_int( const int value ):
                Cardinal_int( unchecked, value )
            { assert( m_value >= 0 ); }

            constexpr auto as_int() const noexcept -> int { return m_value; }
            constexpr operator int() const noexcept { return as_int(); }
        };

        using Ꜿint = Cardinal_int;          // Latin capital letter reversed c with dot, U+A73E.
                                            // Can be short for “Cardinal_int”, and/or
                                            // can be read as short for “counting number”.

        inline namespace cardinal_literals {
            constexpr auto operator ""_cardinal( const unsigned long long int value ) noexcept
                -> Ꜿint
            {
                assert( value <= INT_MAX );
                return Ꜿint( value );
            }

            constexpr auto operator ""_Ꜿ( const unsigned long long int value ) noexcept
                -> Ꜿint
            { return operator""_cardinal( value ); }
        }  // inline namespace cardinal_literals

        constexpr auto Ꜿ0 = 0_cardinal;
        constexpr auto Ꜿ1 = 1_cardinal;

        constexpr auto operator+( const Ꜿint x ) noexcept
            -> Ꜿint
        { return x; }

        constexpr auto operator+( const Ꜿint a, const Ꜿint b ) noexcept
            -> Ꜿint
        { return Ꜿint( tag::Unchecked(), 0 + a + b ); }

        constexpr auto operator+=( Ꜿint& a, const Ꜿint b ) noexcept
            -> Ꜿint&
        { return (a = a + b); }

        constexpr auto operator++( Ꜿint& x ) noexcept
            -> Ꜿint&
        { return (x += Ꜿ1); }

        [[nodiscard]]
        constexpr auto operator++( Ꜿint& x, int ) noexcept
            -> Ꜿint
        {
            const Ꜿint result = x;
            ++x;
            return result;
        }

        constexpr auto operator-( const Ꜿint ) -> int = delete;

        constexpr auto operator-( const Ꜿint a, const Ꜿint b ) noexcept
            -> Ꜿint
        {
            assert( a >= b );
            return Ꜿint( 0 + a - b );
        }

        constexpr auto operator-=( Ꜿint& a, const Ꜿint b ) noexcept
            -> Ꜿint&
        { return (a = a - b); }

        constexpr auto operator--( Ꜿint& x ) noexcept
            -> Ꜿint&
        { return (x -= Ꜿ1); }

        [[nodiscard]]
        constexpr auto operator--( Ꜿint& x, int ) noexcept
            -> Ꜿint
        {
            const Ꜿint result = x;
            --x;
            return result;
        }

        constexpr auto operator*( const Ꜿint a, const Ꜿint b ) noexcept
            -> Ꜿint
        { return Ꜿint( tag::Unchecked(), 1 * a * b ); }

        constexpr auto operator*=( Ꜿint& a, const Ꜿint b ) noexcept
            -> Ꜿint&
        { return (a = a * b); }

        constexpr auto operator/( const Ꜿint a, const Ꜿint b ) noexcept
            -> Ꜿint
        {
            assert( b != 0 );
            return Ꜿint( tag::Unchecked(), 1 * a / b );
        }

        constexpr auto operator/=( Ꜿint& a, const Ꜿint b ) noexcept
            -> Ꜿint&
        { return (a = a / b); }

        // I believe these are from Pascal, where they were named `succ` and `pred`.
        constexpr auto succ_of( const Ꜿint x ) noexcept -> Ꜿint { return Ꜿint( x + 1 ); }
        constexpr auto pred_of( const Ꜿint x ) noexcept -> Ꜿint { return x - Ꜿ1; }

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
