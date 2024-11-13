#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/parameter_passing/data_flow_directions.hpp>      // in_out_
#include <fsm/core/parameter_passing/enabled_if_.hpp>               // enabled_if_

#include <fsm/core/wrapped/c_lib/assert.hpp>            // assert
#include <fsm/core/wrapped/c_lib/limits.hpp>            // INT_MAX

#include <type_traits>

namespace tag {
    using Unchecked = struct Unchecked_struct*;
}  // namesapace tag

namespace fsm_definitions {
    using   fsm::in_out_,                               // parameter_passing/data_flow_directions_.hpp>
            fsm::enabled_if_;                           // parameter_passing/enabled_if_.hpp
    using   std::is_arithmetic_v, std::common_type_t;   // <type_traits>

    namespace basic_type {

        // TODO: numeric_limits specialization
        // TODO: pointer arithmetic
        // TODO: shift operators

        // The notion of a non-negative integer à la Modula-2’s `CARDINAL`.
        //
        // A `Cardinal_int` a.k.a. `Ꜿint`
        //
        // • has the range 0 through `INT_MAX` inclusive, i.e. no negative values ever;
        // • has reasonable magnitude comparison to values of any other arithmetic type;
        // • as a special case supports efficient bounds checking for a range 0 to N;
        // • converts explicitly to `int` via `x.as_int`, `+x` or `-x`; and
        // • with `NDEBUG` defined has checked implicit construction from `int`.
        //
        // In order to avoid annoying explicit conversions of literals to `Cardinal_int`, with
        // this design `int` converts implicitly to `Cardinal_int`, but not vice versa.
        //
        // That hard choice means that mixed type expressions resolve to type `Cardinal_int`.
        //
        class Cardinal_int
        {
            int     m_value     = 0;

        public:
            static constexpr auto unchecked = tag::Unchecked();

            constexpr Cardinal_int( tag::Unchecked, const int value ):
                m_value( value )
            {}

            constexpr Cardinal_int( const int value = 0 ):
                m_value( value )
            { assert( m_value >= 0 ); }

            constexpr auto as_int() const noexcept -> int { return m_value; }
            // constexpr explicit operator int() const noexcept { return as_int(); }

            template< class Integer >
            constexpr operator Integer () const noexcept
            {
                using Common = common_type_t<Integer, int>;

                const auto result = static_cast<Integer>( as_int() );
                assert( Common( result ) == Common( as_int() ) );
                return result;
            }
        };

        using Ꜿint = Cardinal_int;          // Latin capital letter reversed c with dot, U+A73E.
                                            // Can be short for “Cardinal_int”, and/or
                                            // can be read as short for “counting number”.

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
        { return (unsigned( x ) < unsigned( limit.as_int() )); }

        inline namespace cardinal_literals {
            constexpr auto operator ""_cardinal( const unsigned long long int value ) noexcept
                -> Ꜿint
            {
                assert( value <= INT_MAX );
                return Ꜿint( value );
            }

            constexpr auto operator ""_Ꜿint( const unsigned long long int value ) noexcept
                -> Ꜿint
            { return operator""_cardinal( value ); }

            constexpr auto Ꜿ0 = 0_Ꜿint;
            constexpr auto Ꜿ1 = 1_Ꜿint;
        }  // inline namespace cardinal_literals

        inline namespace cardinal_to_int_conversion {
            constexpr auto operator+( const Ꜿint x ) noexcept
                -> int
            { return x.as_int(); }

            constexpr auto operator-( const Ꜿint x ) noexcept
                -> int
            { return -x.as_int(); }
        }  // inline namespace cardinal_to_int_conversion

       inline namespace cardinal_comparison {
            constexpr auto operator< ( const Ꜿint a, const Ꜿint b ) noexcept -> bool { return (+a < +b); }
            constexpr auto operator<=( const Ꜿint a, const Ꜿint b ) noexcept -> bool { return (+a <= +b); }
            constexpr auto operator==( const Ꜿint a, const Ꜿint b ) noexcept -> bool { return (+a == +b); }
            constexpr auto operator>=( const Ꜿint a, const Ꜿint b ) noexcept -> bool { return (+a >= +b); }
            constexpr auto operator> ( const Ꜿint a, const Ꜿint b ) noexcept -> bool { return (+a > +b); }
            constexpr auto operator!=( const Ꜿint a, const Ꜿint b ) noexcept -> bool { return (+a != +b); }

            // TODO: optimize `compare` for unsigned `Number` types.

            template< class Number,
                bool = enabled_if_< is_arithmetic_v< Number > > >
            constexpr auto compare( const Ꜿint a, const Number b ) noexcept
                -> int
            { return (Number( a ) > b) - (Number( a ) < b); }

            template< class Number,
                bool = enabled_if_< is_arithmetic_v< Number > > >
            constexpr auto compare( const Number a, const Ꜿint b ) noexcept
                -> int
            { return (a > Number( b )) - (a < Number( b )); }

            constexpr auto compare( Ꜿint a, const Ꜿint b ) noexcept
                -> int
            { return a.as_int() - b.as_int(); }
        }  // inline namespace cardinal_comparison

        inline namespace cardinal_arithmetic {
            constexpr auto operator+( const Ꜿint a, const Ꜿint b ) noexcept
                -> Ꜿint
            { return Ꜿint( tag::Unchecked(), +a + +b ); }

            constexpr auto operator+=( in_out_<Ꜿint> a, const Ꜿint b ) noexcept
                -> Ꜿint&
            { return (a = a + b); }

            constexpr auto operator++( in_out_<Ꜿint> x ) noexcept
                -> Ꜿint&
            { return (x += Ꜿ1); }

            [[nodiscard]]
            constexpr auto operator++( in_out_<Ꜿint> x, int ) noexcept
                -> Ꜿint
            {
                const Ꜿint result = x;
                ++x;
                return result;
            }

            constexpr auto operator-( const Ꜿint a, const Ꜿint b ) noexcept
                -> Ꜿint
            {
                assert( +a >= +b );
                return Ꜿint( +a - +b );        // Checked.
            }

            constexpr auto operator-=( in_out_<Ꜿint> a, const Ꜿint b ) noexcept
                -> Ꜿint&
            { return (a = a - b); }

            constexpr auto operator--( in_out_<Ꜿint> x ) noexcept
                -> Ꜿint&
            { return (x -= Ꜿ1); }

            [[nodiscard]]
            constexpr auto operator--( in_out_<Ꜿint> x, int ) noexcept
                -> Ꜿint
            {
                const Ꜿint result = x;
                --x;
                return result;
            }

            constexpr auto operator*( const Ꜿint a, const Ꜿint b ) noexcept
                -> Ꜿint
            { return Ꜿint( tag::Unchecked(), +a * +b ); }

            constexpr auto operator*=( in_out_<Ꜿint> a, const Ꜿint b ) noexcept
                -> Ꜿint&
            { return (a = a * b); }

            constexpr auto operator/( const Ꜿint a, const Ꜿint b ) noexcept
                -> Ꜿint
            {
                assert( +b != 0 );
                return Ꜿint( tag::Unchecked(), +a / +b );
            }

            constexpr auto operator/=( in_out_<Ꜿint> a, const Ꜿint b ) noexcept
                -> Ꜿint&
            { return (a = a / b); }

            constexpr auto operator%( const Ꜿint a, const Ꜿint b ) noexcept
                -> Ꜿint
            {
                assert( +b != 0 );
                return Ꜿint( tag::Unchecked(), +a % +b );
            }

            constexpr auto operator%=( in_out_<Ꜿint> a, const Ꜿint b ) noexcept
                -> Ꜿint&
            { return (a = a % b); }

            // In Pascal these were built-ins named `succ` and `pred`:
            constexpr auto next_of( const Ꜿint x ) noexcept -> Ꜿint { return x + 1; }
            constexpr auto prev_of( const Ꜿint x ) noexcept -> Ꜿint { return x - 1; }
        }  // inline namespace cardinal_arithmetic
    }  // namespace basic_type
}  // namespace fsm_definitions

namespace fsm {
    inline namespace basic_type{ using namespace fsm_definitions::basic_type; }
}  // namespace fsm
