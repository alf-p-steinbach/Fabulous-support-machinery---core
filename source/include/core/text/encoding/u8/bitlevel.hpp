#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/basic_type/bit_operations/Bitpattern_.hpp>           // Bitpattern_
#include <fsm/core/basic_type/Cardinal_int.hpp>                         // Ꜿint, Ꜿ1
#include <fsm/core/basic_type/names/Byte.hpp>                           // Byte
#include <fsm/core/exception_handling/FSM_FAIL.hpp>                     // now, $fail
#include <fsm/core/type_builders.hpp>                                   // const_

#include <cassert>      // assert macro

namespace fsm_definitions {
    using namespace fsm::cardinal_literals;
    using   fsm::Bitpattern_,                           // basic_type/bit_operations/Bitpattern_.hpp
            fsm::Ꜿint, fsm::Ꜿ1,                         // basic_type/Cardinal_int.hpp
            fsm::Byte,                                  // basic_type/names/Byte.hpp
            fsm::now,                                   // exception_handling/FSM_FAIL.hpp
            fsm::const_;                                // type_builders.hpp

    namespace text::u8 {
        constexpr auto  ascii_pattern       = Bitpattern_<Byte>( "0xxx'xxxx" );
        constexpr auto  headbyte_pattern    = Bitpattern_<Byte>( "11xx'xxxx" );
        constexpr auto  tailbyte_pattern    = Bitpattern_<Byte>( "10xx'xxxx" );

        constexpr Ꜿint n_tailbyte_value_bits   = tailbyte_pattern.n_value_bits();      // 6

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
        { return tailbyte_pattern.value_bits_of( unit ); }

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
            if( (first_byte & 0b1000'0000) == 0 ) { return 0_cardinal; }
            if( (first_byte & 0b0010'0000) == 0 ) { return 1_cardinal; }
            if( (first_byte & 0b0001'0000) == 0 ) { return 2_cardinal; }
            if( (first_byte & 0b1000'1000) == 0 ) { return 3_cardinal; }
            // assert( !"oops, invalid head byte (max 3 tail bytes permitted)" );
            if( (first_byte & 0b1000'0100) == 0 ) { return 4_cardinal; }
            if( (first_byte & 0b1000'0010) == 0 ) { return 5_cardinal; }
            if( (first_byte & 0b1000'0001) == 0 ) { return 6_cardinal; }
            return 7_cardinal;
        }

        // The formal limit on number of tailbytes, 3, is not enforced.
        constexpr auto seq_length_of( const Byte first_byte )
            -> Ꜿint
        { return n_tailbytes_after( first_byte ) + Ꜿ1; }

        constexpr auto is_valid_headbyte( const Byte unit )
            -> bool
        { return is_headbyte( unit ) and n_tailbytes_after( unit ) <= 3; }

        constexpr auto codepoint_from( const_<const Byte*> p_first )
            -> char32_t
        {
            const Byte  first_byte      = *p_first;
            const Ꜿint  n_tailbytes     = n_tailbytes_after( first_byte );

            if( n_tailbytes == 0 ) {
                return first_byte;          // ASCII.
            }

            const Byte* p = p_first;
            char32_t result = headbyte_value_of( first_byte );
            for( Ꜿint i = Ꜿ1; i <= n_tailbytes; ++i ) {
                ++p;
                result <<= +n_tailbyte_value_bits;
                result |= tailbyte_value_of( *p );
            }
            return result;
        }

        constexpr auto to_seq_at( const_<Byte*> p_start, const char32_t code )
            -> Ꜿint    // Length of sequence including head byte.
        {
            const auto seq = p_start;
            if( code < 0x80 ) {                                             // 7 bits as 7
                seq[0] = code;
                return Ꜿ1;
            }

            const auto n_tailbytes = Ꜿint(
                //  5 + 1×6 = 11          4 + 2×6 = 16            3 + 3×6 = 21
                    code < 0x800? 1     : code < 0x10000? 2     : code < 0x110000? 3
                : 666
                );
            now( n_tailbytes != 666 ) or $fail( "Invalid Unicode code point (≥ 0x110000)." );

            auto bits = code;
            for( Byte* p = p_start + +n_tailbytes; p != p_start; --p ) {     // N ×
                *p = tailbyte_pattern.with_value_bits( Byte( bits ) );      // 6 bits.
                bits >>= +n_tailbyte_value_bits;
            }
            const auto head_byte_signature = Byte( ~((0b1000'0000u >> +n_tailbytes) - 1) );
            // assert( headbyte_pattern.matches( head_byte_signature ) );
            *p_start = Byte( bits | head_byte_signature );                  // Remaining bits.
            return n_tailbytes + Ꜿ1;
        }
    }  // namespace text::u8
}  // namespace fsm_definitions

namespace fsm {
    inline namespace text { using namespace fsm_definitions::text; }
}  // namespace fsm
