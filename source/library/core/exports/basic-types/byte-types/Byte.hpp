#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

// The C++17 `std::byte` + usually necessary support.
//
// Note: C++17 introduced a number of differences between some <cFOO> headers and
// corresponding <FOO.h> headers. In particular `<cmath>` received a large number
// of special functions from C11, and `<cstddef>` got `std::byte`. So to get
// `std::byte` you need to include `<cstddef>`; just including `<stddef.h>` alone
// does not suffice.
//
#include <cstddef>  // Supplies `<std::byte>`.
#include <stddef.h> // Avoids problems with /inadvertent/ use of stuff from `::`.

#include <fsm/core/exports/basic-types/byte-types/byte-info.hpp>     // bits_per_byte
#include <fsm/core/exports/basic-types/byte-types/Byte_number.hpp>   // Byte_number
#include <fsm/core/exports/basic-types/Literal_null.hpp>             // Literal_null

namespace fabulous_support_machinery {

    using Byte = std::byte;
    
    // The standard library defines bit-level operators for `std::byte`, namely
    // `<<`, `>>`, `|`, `&`, `^`, `~`, and ditto update (assignment) operators.
    //
    // The following are convenience ops for dealing with bytes as numbers:
    //
    inline namespace byte_as_integer {
        constexpr auto operator+( const Byte v )
            -> Byte_number
        { return std::to_integer<Byte_number>( v ); }

        constexpr auto operator==( const Byte v, Literal_null )
            -> bool
        { return (+v == 0); }

        constexpr auto operator==( Literal_null, const Byte v )
            -> bool
        { return (+v == 0); }

        constexpr auto operator!=( const Byte v, Literal_null )
            -> bool
        { return (+v != 0); }

        constexpr auto operator!=( Literal_null, const Byte v )
            -> bool
        { return (+v != 0); }
    }  // namespace byte_as_integer

}  // namespace fabulous_support_machinery
