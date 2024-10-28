#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/basic_type/names/Byte.hpp>                           // Byte
#include <fsm/core/collection_support/size_functions.hpp>               // int_size_of
#include <fsm/core/constructs/FSM_NSNAME_FROM.hpp>                      // FSM_NSNAME_FROM
#include <fsm/core/exception_handling/FSM_FAIL.hpp>                     // hopefully, FSM_FAIL

namespace fsm_definitions {

    namespace text::u8 {
        
    }  // namespace text::u8
}  // namespace fsm_definitions

namespace fsm {
    inline namespace text { using namespace fsm_definitions::text; }
}  // namespace fsm

#if 0
namespace fsm_definitions::u8 {
    namespace fsm = fabulous_support_machinery;
    using   fsm::Byte,
            fsm::int_size_of,
            fsm::hopefully;

    namespace continuation_bytes {
        constexpr int   n_value_bits    = 6;
        constexpr auto  value_bits_mask = Byte( (1u << n_value_bits) - 1 );
        constexpr auto  head_mask       = Byte( 0b11u << n_value_bits );
        constexpr auto  head_pattern    = Byte( 0b10u << n_value_bits );

        FSM_STATIC_ASSERT( value_bits_mask == (~head_mask & Byte( 0xFF )) );

        constexpr auto byte_set_contains( const Byte unit ) noexcept
            -> bool
        { return ((unit & head_mask) == head_pattern); }

        constexpr auto value_bits_of( const Byte unit ) noexcept
            -> Byte
        { return unit & value_bits_mask; }
    }  // namespace continuation_bytes

    constexpr auto is_continuation_byte( const Byte unit ) noexcept
        -> bool
    { return continuation_bytes::byte_set_contains( unit ); }
    
    namespace lead_bytes {
        constexpr auto  upper_bits_mask     = Byte( 0b11111u << 3 );
        constexpr int   n_lengths           = 4;
        constexpr Byte  single_bit_masks[]  =
        {
            Byte( 1u << 7 ), Byte( 1u << 6 ), Byte( 1u << 5 ), Byte( 1u << 4 ), Byte( 1u << 3 )
        };

        static_assert( int_size_of( single_bit_masks ) == n_lengths + 1 );

        constexpr Byte value_bits_masks[] =
        {
            Byte( (1u << 7) - 1 ), Byte( (1u << 6) - 1 ), Byte( (1u << 5) - 1 ), Byte( (1u << 4) - 1 ), Byte( (1u << 3) - 1 )
        };
        static_assert( int_size_of( value_bits_masks ) == n_lengths + 1 );

        constexpr auto byte_set_contains( const Byte unit )  noexcept
            -> bool
        {
            const Byte upper_bits = (unit & upper_bits_mask);
            return (not is_continuation_byte( unit )) and upper_bits != upper_bits_mask;
        }
        
        constexpr auto sequence_length_of( const Byte lead_byte ) noexcept(false)
            -> int
        {
            const auto bits = lead_byte;
            if( (bits & single_bit_masks[0]) == 0 ) { return 1; }
            hopefully( (bits & single_bit_masks[1]) != 0 )
                or FSM_FAIL( "Invalid lead byte (bit pattern reserved for continuation_bytess)" );
            if( (bits & single_bit_masks[2]) == 0 ) { return 2; }
            if( (bits & single_bit_masks[3]) == 0 ) { return 3; }
            if( (bits & single_bit_masks[4]) == 0 ) { return 4; }
            FSM_FAIL( "Invalid lead byte (specifies a more than 4 bytes sequence)." );
            for( ;; ) {}    // Should not get here.
        }
        
        constexpr auto value_bits_of( const Byte lead_byte, const int n_bytes ) noexcept
            -> Byte
        { return lead_byte & value_bits_masks[n_bytes - (n_bytes == 1)]; }

        constexpr auto value_bits_of( const Byte lead_byte ) noexcept(false)
            -> Byte
        { return value_bits_of( lead_byte, sequence_length_of( lead_byte ) ); }
    }  // namespace lead_bytes

    constexpr auto is_lead_byte( const Byte unit ) noexcept
        -> bool
    { return lead_bytes::byte_set_contains( unit ); }
    
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

    namespace x = u8;

    namespace exports { using
        x::is_continuation_byte,
        x::is_lead_byte;

        namespace continuation_bytes    { using namespace x::continuation_bytes; }
        namespace lead_bytes            { using namespace x::lead_bytes; }
        namespace byte_sequence         { using namespace x::byte_sequence; }
    }  // namespace exports
}  // namespace fsm_definitions::u8

namespace fabulous_support_machinery{
    // `u8::` stuff is intentionally not available unqualified in fsm namespace.

    // Not a simple equate because may need to be an extension of earlier declared namespace.
    namespace u8{
        using namespace fsm_definitions::u8::exports;
    }  // namespace u8
}  // namespace fabulous_support_machinery
#endif
