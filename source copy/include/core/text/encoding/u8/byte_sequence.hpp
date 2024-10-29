#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

namespace fsm_definitions {
}  // namespace fsm_definitions

namespace fsm {
    inline namespace text { using namespace fsm_definitions::text; }
}  // namespace fsm

#if 0
    namespace byte_sequence {
        using   std::iterator_traits;

        constexpr int   max_length  = lead_bytes::n_lengths;

        struct Validity{ enum Enum{ valid = false, invalid_lead_byte, invalid_continuation_byte }; };
        
        template< class Unit_iterator >
        constexpr auto validity_of( const Unit_iterator it )
            -> Validity::Enum
        {
            if( not is_lead_byte( Byte( *it ) ) ) {
                return Validity::invalid_lead_byte;
            } else {
                const int n_bytes = lead_bytes::sequence_length_of( Byte( *it ) );
                for( int i = 1; i < n_bytes; ++i ) {
                    if( not is_continuation_byte( Byte( *(it + i) ) ) ) {
                        return Validity::invalid_continuation_byte;
                    }
                }
            }
            return Validity::valid;
        }

        template< class Unit_iterator >
        constexpr auto checked( const Unit_iterator it )
            -> Unit_iterator
        {
            switch( validity_of( it ) ) {
                case Validity::valid:                        return it;
                case Validity::invalid_lead_byte:            FSM_FAIL( "Invalid lead byte" );
                case Validity::invalid_continuation_byte:    FSM_FAIL( "Invalid continuation_bytes" );
            }
            for( ;; ) {}        // Should never get here.
        }

        template< class Unit_iterator >
        constexpr auto to_codepoint( Unit_iterator it )
            -> char32_t
        {
            const auto  lead_byte   = Byte( *it );
            const int   length      = lead_bytes::sequence_length_of( lead_byte );
            
            char32_t result = +lead_bytes::value_bits_of( lead_byte, length );
            for( int i = 1; i < length; ++i ) {
                ++it;
                result <<= continuation_bytes::n_value_bits;
                result |= +continuation_bytes::value_bits_of( Byte( *it ) );
            }
            return result;
        }

        template< class Unit_iterator >
        constexpr auto to_sequence_at( const Unit_iterator it, const char32_t code )
            -> int
        {
            using Unit = typename iterator_traits<Unit_iterator>::value_type;
                if( code < 0x80 ) {                                 // 7 bits as 7
                *(it + 0) = static_cast<Unit>( code );
                return 1;
            } else if( code < 0x800 ) {                             // 11 bits as 5 + 6
                char32_t bits = code;
                *(it + 1) = static_cast<Unit>( bits & +continuation_bytes::value_bits_mask );   // 6
                bits >>= continuation_bytes::n_value_bits;
                *(it + 0) = static_cast<Unit>( 0b1100'0000 | bits );                            // 5
                return 2;
            } else if( code < 0x10000 ) {                           // 16 bits as 4 + 6 + 6
                char32_t bits = code;
                *(it + 2) = static_cast<Unit>( bits & +continuation_bytes::value_bits_mask );   // 6
                bits >>= continuation_bytes::n_value_bits;
                *(it + 1) = static_cast<Unit>( bits & +continuation_bytes::value_bits_mask );   // 6
                bits >>= continuation_bytes::n_value_bits;
                *(it + 0) = static_cast<Unit>( 0b1110'0000 | bits );                            // 4
                return 3;
            } else if( code < 0x110000 ) {                          // 21 bits as 3 + 6 + 6 + 6
                char32_t bits = code;
                *(it + 3) = static_cast<Unit>( bits & +continuation_bytes::value_bits_mask );   // 6
                bits >>= continuation_bytes::n_value_bits;
                *(it + 2) = static_cast<Unit>( bits & +continuation_bytes::value_bits_mask );   // 6
                bits >>= continuation_bytes::n_value_bits;
                *(it + 1) = static_cast<Unit>( bits & +continuation_bytes::value_bits_mask );   // 6
                bits >>= continuation_bytes::n_value_bits;
                *(it + 0) = static_cast<Unit>( 0b1111'0000 | bits );                            // 3
                return 4;
            } else {
                FSM_FAIL( "Invalid Unicode code point (≥ 0x110000)." );
            }
            for( ;; ) {}    // Should never get here.
        }
    }  // namespace byte_sequence

#endif
