#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/basic_type/bit_operations/Bitpattern_.hpp>           // Bitpattern_
#include <fsm/core/basic_type/byte_operations/byte_ptr_cast.hpp>        // byte_ptr_cast
#include <fsm/core/basic_type/Cardinal_int.hpp>                         // Cint
#include <fsm/core/basic_type/names/Byte.hpp>                           // Byte
#include <fsm/core/exception/throwing/FSM_FAIL.hpp>                     // now, $fail
#include <fsm/core/type_builders.hpp>                                   // const_

#include <cassert>      // assert macro

namespace fsm_definitions {
    using namespace fsm::cardinal_literals;
    using   fsm::Bitpattern_,                           // basic_type/bit_operations/Bitpattern_.hpp
            fsm::byte_ptr_cast,                         // basic_type/byte_operations/byte_ptr_cast.hpp
            fsm::Cint,                                  // basic_type/Cardinal_int.hpp
            fsm::Byte,                                  // basic_type/names/Byte.hpp
            fsm::now,                                   // exception_handling/FSM_FAIL.hpp
            fsm::const_;                                // type_builders.hpp

    namespace text::u8 {
        constexpr Cint  max_seq_length      = 4;        // As of 2024. Could be up to and including 7.
        constexpr Cint  max_tailbytes       = max_seq_length - 1;

        constexpr auto  asciibyte_pattern   = Bitpattern_<Byte>( "0xxx'xxxx" );
        constexpr auto  headbyte_pattern    = Bitpattern_<Byte>( "11xx'xxxx" );
        constexpr auto  tailbyte_pattern    = Bitpattern_<Byte>( "10xx'xxxx" );

        constexpr Cint n_tailbyte_value_bits   = tailbyte_pattern.n_value_bits();      // 6

        constexpr auto is_asciibyte( const Byte unit ) noexcept
            -> bool
        { return asciibyte_pattern.matches( unit ); }

        constexpr auto is_tailbyte( const Byte unit ) noexcept
            -> bool
        { return tailbyte_pattern.matches( unit ); }

        constexpr auto is_headbyte( const Byte unit ) noexcept
            -> bool
        { return headbyte_pattern.matches( unit ); }

        constexpr auto is_seq_start( const Byte unit ) noexcept
            -> bool
        { return not is_tailbyte( unit ); }     // = `is_asciibyte( unit ) or is_headbyte( unit )`
 
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
            -> Cint
        {
            if( (first_byte & 0b1000'0000) == 0 ) { return 0; }
            if( (first_byte & 0b0010'0000) == 0 ) { return 1; }
            if( (first_byte & 0b0001'0000) == 0 ) { return 2; }
            if( (first_byte & 0b1000'1000) == 0 ) { return 3; }
            // assert( !"oops, invalid head byte (max 3 tail bytes permitted)" );
            if( (first_byte & 0b1000'0100) == 0 ) { return 4; }
            if( (first_byte & 0b1000'0010) == 0 ) { return 5; }
            if( (first_byte & 0b1000'0001) == 0 ) { return 6; }
            return 0;       // Invalid head byte but return 0 to possibly skip 1 byte.
        }

        // The formal limit on number of tailbytes, 3, is not enforced.
        constexpr auto seq_length_of( const Byte first_byte )
            -> Cint
        { return n_tailbytes_after( first_byte ) + 1; }

        constexpr auto is_valid_headbyte( const Byte unit )
            -> bool
        { return is_headbyte( unit ) and n_tailbytes_after( unit ) <= 3; }

        constexpr auto codepoint_from( const_<const Byte*> p_first )
            -> char32_t
        {
            const Byte  first_byte      = *p_first;
            const Cint  n_tailbytes     = n_tailbytes_after( first_byte );

            if( n_tailbytes == 0 ) {
                return first_byte;          // ASCII.
            }

            const Byte* p = p_first;
            char32_t result = headbyte_value_of( first_byte );
            for( Cint i = 1; i <= n_tailbytes; ++i ) {
                ++p;
                result <<= +n_tailbyte_value_bits;
                result |= tailbyte_value_of( *p );
            }
            return result;
        }

        constexpr auto codepoint_from( const_<const char*> p_first )
            -> char32_t
        { return codepoint_from( byte_ptr_cast( p_first ) ); }

        constexpr auto to_seq_at( const_<Byte*> p_start, const char32_t code )
            -> Cint    // Length of sequence including head byte.
        {
            const auto seq = p_start;
            if( code < 0x80 ) {                                             // 7 bits as 7
                seq[0] = code;
                return 1;
            }

            const auto n_tailbytes = Cint(
                //  5 + 1×6 = 11          4 + 2×6 = 16            3 + 3×6 = 21
                    code < 0x800? 1     : code < 0x10000? 2     : code < 0x110000? 3
                : 666
                );
            now( n_tailbytes != 666 ) or $fail( "Invalid Unicode code point (≥ 0x110000)." );

            auto bits = code;
            for( Byte* p = p_start + +n_tailbytes; p != p_start; --p ) {    // N ×
                *p = tailbyte_pattern.with_value_bits( Byte( bits ) );      // 6 bits.
                bits >>= +n_tailbyte_value_bits;
            }
            const auto head_byte_signature = Byte( ~((0b1000'0000u >> +n_tailbytes) - 1) );
            // assert( headbyte_pattern.matches( head_byte_signature ) );
            *p_start = Byte( bits | head_byte_signature );                  // Remaining bits.
            return n_tailbytes + 1;
        }

        constexpr auto to_seq_at( const_<char*> p_start, const char32_t code )
            -> Cint    // Length of sequence including head byte.
        { return to_seq_at( byte_ptr_cast( p_start ), code ); }
    }  // namespace text::u8
}  // namespace fsm_definitions

namespace fsm {
    inline namespace text { using namespace fsm_definitions::text; }
}  // namespace fsm
