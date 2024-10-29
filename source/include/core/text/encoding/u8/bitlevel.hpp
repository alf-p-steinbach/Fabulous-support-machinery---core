#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/basic_type/bit_operations/Bitpattern_.hpp>           // Bitpattern_
#include <fsm/core/basic_type/Cardinal_int.hpp>                         // Ꜿint, Ꜿ1
#include <fsm/core/basic_type/names/Byte.hpp>                           // Byte
#include <fsm/core/collection_support/size_functions.hpp>               // int_size_of
#include <fsm/core/constructs/FSM_NSNAME_FROM.hpp>                      // FSM_NSNAME_FROM
#include <fsm/core/exception_handling/FSM_FAIL.hpp>                     // hopefully, FSM_FAIL

#include <cassert>      // assert macro

namespace fsm_definitions {
    using   fsm::Bitpattern_,                               // basic_type/bit_operations/Bitpattern_.hpp
            fsm::Byte,                                      // basic_type/names/Byte.hpp
            fsm::Ꜿint, fsm::Ꜿ1;                             // basic_type/Cardinal_int.hpp

    namespace text::u8 {
        constexpr auto  ascii_pattern       = Bitpattern_<Byte>( "0xxx'xxxx" );
        constexpr auto  tailbyte_pattern    = Bitpattern_<Byte>( "10xx'xxxx" );
        constexpr auto  headbyte_pattern    = Bitpattern_<Byte>( "11xx'xxxx" );

        constexpr auto is_ascii_byte( const Byte unit ) noexcept
            -> bool
        { return ascii_pattern.matches( unit ); }

        constexpr auto is_tailbyte( const Byte unit ) noexcept
            -> bool
        { return tailbyte_pattern.matches( unit ); }

        constexpr auto is_headbyte( const Byte unit ) noexcept
            -> bool
        { return headbyte_pattern.matches( unit ); }

        // Unspecified if the unit is not a tailbyte.
        constexpr auto tailbyte_value_of( const Byte unit ) noexcept
            -> Byte
        { return unit & 0b0011'1111; }

        // Unspecified if the unit is not a headbyte,
        // except that the formal limit on number of tailbytes, 3, is not enforced.
        constexpr auto headbyte_value_of( const Byte unit ) noexcept
            -> Byte
        {
            Byte highest_zero = 0b0010'0000;
            while( highest_zero & unit ) { highest_zero >>= 1; }
            return (highest_zero? unit & (highest_zero - 1) : 0);
        }

        // The formal limit on number of tailbytes, 3, is not enforced.
        constexpr auto n_tailbytes_after( const Byte first_byte )
            -> Ꜿint
        {
            if( (first_byte & 0b1000'0000) == 0 ) { return Ꜿint( 0 ); }
            if( (first_byte & 0b0010'0000) == 0 ) { return Ꜿint( 1 ); }
            if( (first_byte & 0b0001'0000) == 0 ) { return Ꜿint( 2 ); }
            if( (first_byte & 0b1000'1000) == 0 ) { return Ꜿint( 3 ); }
            // assert( !"oops, invalid head byte (max 3 tail bytes permitted)" );
            if( (first_byte & 0b1000'0100) == 0 ) { return Ꜿint( 4 ); }
            if( (first_byte & 0b1000'0010) == 0 ) { return Ꜿint( 5 ); }
            if( (first_byte & 0b1000'0001) == 0 ) { return Ꜿint( 6 ); }
            return Ꜿint( 7 );
        }

        // The formal limit on number of tailbytes, 3, is not enforced.
        constexpr auto seq_length_of( const Byte first_byte )
            -> Ꜿint
        { return n_tailbytes_after( first_byte ) + Ꜿ1; }

        constexpr auto is_valid_headbyte( const Byte unit )
            -> bool
        { return is_headbyte( unit ) and n_tailbytes_after( unit ) <= 3; }
    }  // namespace text::u8
}  // namespace fsm_definitions

namespace fsm {
    inline namespace text { using namespace fsm_definitions::text; }
}  // namespace fsm
