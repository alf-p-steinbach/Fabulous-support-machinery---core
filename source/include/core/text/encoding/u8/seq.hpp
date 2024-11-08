#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/text/encoding/u8/bitlevel.hpp>

namespace fsm_definitions {
    namespace text::u8 { inline namespace seq {
        // For exposition only (but also guarantees that these identifiers exist),
        // from the "bitlevel.hpp" header:
        using   text::u8::max_seq_length, text::u8::seq_length_of,
                text::u8::is_ascii_byte, text::u8::is_headbyte, text::u8::is_tailbyte;

        struct Validity{ enum Enum{
            valid,
            invalid_headbyte,                   // Bit pattern doesn't match.
            invalid_seq_length,                 // > max_length bytes.
            invalid_tailbyte                    // Bit pattern doesn't match.
        }; };
        
        // Array locations `p[0]` through `p[seq_length_of( p[0] ) - 1]` must exist.
        constexpr auto validity_of( const_<const Byte*> p )
            -> Validity::Enum
        {
            const auto code = Byte( *p );
            if( is_ascii_byte( code ) )     { return Validity::valid; }

            if( not is_headbyte( code ) )   { return Validity::invalid_headbyte; }

            const Ꜿint n_bytes = seq_length_of( code );
            if( n_bytes > max_seq_length )  { return Validity::invalid_seq_length; }

            for( int i = 1; i < n_bytes; ++i ) {
                if( not is_tailbyte( Byte( p[i] ) ) ) {
                    return Validity::invalid_tailbyte;
                }
            }
            return Validity::valid;
        }

        // Array locations `p[0]` through `p[seq_length_of( p[0] ) - 1]` must exist.
        constexpr auto checked( const_<const Byte*> p )
            -> const Byte*
        {
            using V = Validity;
            switch( validity_of( p ) ) {
                case V::valid:                  break;
                case V::invalid_headbyte:       FSM_FAIL( "Invalid UTF-8 sequence lead byte." );
                case V::invalid_seq_length:     FSM_FAIL( "Invalid (too long) UTF-8 sequence length." );
                case V::invalid_tailbyte:       FSM_FAIL( "Invalid UTF-8 sequence tailbyte." );
            }
            return p;
        }
    } }  // namespace u8::text, inline namespace seq
}  // namespace fsm_definitions

namespace fsm {
    inline namespace text { using namespace fsm_definitions::text; }
}  // namespace fsm
