#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

// The C++17 `std::byte` + in practice necessary support.
//
// Note: to get `std::byte` you need to include `<cstddef>`; `<stddef.h>` alone
// does not suffice.
//
#include <cstddef>  // Supplies `<std::byte>`.
#include <stddef.h> // Avoids problems with /inadvertent/ use of stuff from `::`.

#include <fsm/core/types/fundamental/byte-types/Byte.hpp>         // Byte, bits_per_byte
#include <fsm/core/misc/Literal_null.hpp>                   // Literal_null

namespace fabulous_support_machinery {

    using Safe_byte = std::byte;
    
    // The standard library defines bit-level operators for `std::byte`, namely
    // `<<`, `>>`, `|`, `&`, `^`, `~`, and ditto update (assignment) operators.
    //
    // The following are convenience ops for dealing with bytes as numbers:
    //
    inline namespace byte_as_integer_ops {      // +x, -x, (x == 0), (x != 0)
        constexpr auto operator+( const Safe_byte v )
            -> Byte
        { return std::to_integer<Byte>( v ); }

        constexpr auto operator-( const Safe_byte v )
            -> Byte
        { return -std::to_integer<Byte>( v ); }


        constexpr auto operator==( const Safe_byte v, Literal_null )
            -> bool
        { return (+v == 0); }

        constexpr auto operator==( Literal_null, const Safe_byte v )
            -> bool
        { return (+v == 0); }


        constexpr auto operator!=( const Safe_byte v, Literal_null )
            -> bool
        { return (+v != 0); }

        constexpr auto operator!=( Literal_null, const Safe_byte v )
            -> bool
        { return (+v != 0); }
    }  // namespace byte_as_integer_ops

}  // namespace fabulous_support_machinery
