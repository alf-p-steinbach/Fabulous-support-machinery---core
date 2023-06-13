#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

// Mostly for use in template programming, e.g. FSM_ENABLE_IF expressions.

#include <fsm/core/constructs/declarations/type_builders.hpp>       // in_

#include <utility>

namespace fsm_definitions::number_ops {
    namespace fsm = fabulous_support_machinery;
    using   fsm::in_;
    using   std::forward;       // <utility>

    template< class Integer >
    constexpr auto is_even( const Integer x ) -> bool { return (x % 2 == 0); }

    template< class Integer >
    constexpr auto is_odd( const Integer x ) -> bool { return (x % 2 == 1); }

    template< class Int >
    constexpr inline auto quotient_rounded_down_of( const Int a, const Int b ) noexcept
        -> Int
    {
        const Int q = a/b;
        return (q < 0 and a % b != 0? q - 1 : q);
    }

    template< class Int >
    constexpr inline auto quotient_rounded_up_of( const Int a, const Int b ) noexcept
        -> Int
    {
        const Int q = a/b;
        return (q >= 0 and a % b != 0? q + 1 : q);
    }

    template< class Int >
    constexpr inline auto math_mod_of( const Int a, const Int b ) noexcept
        -> Int
    { return a - b*quotient_rounded_down_of( a, b ); }

    template< class Number >
    constexpr auto is_zero( const Number x ) -> bool { return (x == 0); }

    template< class Number >
    constexpr auto squared( const Number x ) -> Number { return x*x; }

    template< class Number >
    constexpr auto cubed( const Number x ) -> Number { return x*x*x; }

    // Essentially this is Horner's rule adapted to calculating a power, so that the
    // number of floating point multiplications is at worst O(log2(n)).
    constexpr inline auto basic_intpow_of( const double base, const int exponent )
        -> double
    {
        double result = 1;
        double weight = base;
        for( int n = exponent; n != 0; weight *= weight ) {
            if( is_odd( n ) ) {
                result *= weight;
            }
            n /= 2;
        }
        return result;
    }

    constexpr inline auto intpow_of( const double base, const int exponent )
        -> double
    {
        return (0?double()
            : exponent == 0?        1.0
            : exponent < 0?         1.0/basic_intpow_of( base, -exponent )
            :                       basic_intpow_of( base, exponent )
            );
    }

    namespace x = number_ops;
    namespace exports { using
        x::is_even,
        x::is_odd,
        x::quotient_rounded_down_of,
        x::quotient_rounded_up_of,
        x::math_mod_of,
        x::is_zero,
        x::squared,
        x::cubed,
        x::intpow_of;
    }
}  // namespace fsm_definitions::boolean_ops

namespace fabulous_support_machinery{
    using namespace fsm_definitions::number_ops::exports;

    // Not a simple equate because may need to be an extension of earlier declared namespace.
    namespace number_ops{
        using namespace fsm_definitions::number_ops::exports;
    }  // namespace number_ops
}  // namespace fabulous_support_machinery
