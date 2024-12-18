#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/basic_type/byte_operations/byte_ptr_cast.hpp>
#include <fsm/core/text/encoding/u8/seq.hpp>

#include <string_view>

namespace fsm_definitions {
    using   fsm::byte_ptr_cast, fsm::byte_ptr_cast_;

    using   std::string_view;           // <string_view>

    namespace text::u8 { inline namespace seq {

        // Array locations `p[0]` through `p[seq_length_of( p[0] ) - 1]` must exist.
        constexpr auto validity_of( const_<const char*> p )
            -> Validity::Enum
        { return validity_of( byte_ptr_cast( p ) ); }

        // Array locations `p[0]` through `p[seq_length_of( p[0] ) - 1]` must exist.
        constexpr auto checked( const_<const char*> p )
            -> const char*
        { return byte_ptr_cast_<const char>( checked( byte_ptr_cast( p ) ) ); }

        constexpr auto p_seq_after( const_<const char*> p_seq )
            -> const char*
        { return byte_ptr_cast_<const char>( p_seq_after( byte_ptr_cast( p_seq ) ) ); }

        constexpr auto capped_p_seq_after(
            const_<const char*>     p_seq,
            const Nat              max_length = max_seq_length
            ) -> const char*
        { return byte_ptr_cast_<const char>( capped_p_seq_after( byte_ptr_cast( p_seq ), max_length ) ); }

        constexpr auto p_seq_before( const_<const char*> p_seq )
            -> const char*
        { return byte_ptr_cast_<const char>( p_seq_before( byte_ptr_cast( p_seq ) ) ); }

        constexpr auto capped_p_seq_before(
            const_<const char*>     p_seq,
            const Nat              max_length = max_seq_length
            ) -> const char*
        { return byte_ptr_cast_<const char>( capped_p_seq_before( byte_ptr_cast( p_seq ), max_length ) ); }

        constexpr void move_to_next( const char*& p_seq )
        {
            p_seq = byte_ptr_cast_<const char>( p_seq_after( byte_ptr_cast( p_seq ) ) );
        }

        constexpr void capped_move_to_next(
            const char*&    p_seq,
            const Nat      max_length = max_seq_length
            )
        {
            p_seq = byte_ptr_cast_<const char>( capped_p_seq_after( byte_ptr_cast( p_seq ), max_length ) );
        }

        constexpr void move_to_prev( const char*& p_seq )
        {
            p_seq = byte_ptr_cast_<const char>( p_seq_before( byte_ptr_cast( p_seq ) ) );
        }

        constexpr void capped_move_to_prev(
            const char*&    p_seq,
            const Nat      max_length = max_seq_length
            )
        {
            p_seq = byte_ptr_cast_<const char>( capped_p_seq_before( byte_ptr_cast( p_seq ), max_length ) );
        }

        constexpr auto string_view_of( const_<const char*> p_seq )
            -> string_view
        { return string_view( p_seq, seq_length_of( *byte_ptr_cast( p_seq ) ) ); }

    } }  // namespace u8::text, inline namespace seq
}  // namespace fsm_definitions

namespace fsm {
    inline namespace text { using namespace fsm_definitions::text; }
}  // namespace fsm
