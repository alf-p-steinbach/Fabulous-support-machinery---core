#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/text/encoding/u8/Cp_iterator_.hpp>           // fsm::u8::*
#include <fsm/core/constructs/declarations/FSM_NS_FROM.hpp>     // FSM_NS_FROM

#include <optional>
#include <string_view>
#include <variant>

#include <assert.h>

namespace fsm_definitions::unicode {
    namespace fsm = fabulous_support_machinery;
    FSM_NS_FROM( fsm, u8 );
    using   fsm::in_;
    using   std::optional, std::holds_alternative, std::get,        // <optional>
            std::string_view,                                       // <string_view>
            std::variant;                                           // <variant>

    struct Special_display_widths{ enum Enum{
        // Values & comments from <url: https://github.com/ridiculousfish/widecharwidth/>.
        nonprint        = -1,       // The character is not printable.
        combining       = -2,       // The character is a zero-width combiner.
        ambiguous       = -3,       // The character is East-Asian ambiguous width.
        private_use     = -4,       // The character is for private use.
        unassigned      = -5,       // The character is unassigned.
        widened_in_9    = -6,       // Width is 1 in Unicode 8, 2 in Unicode 9+.
        non_character   = -7        // The character is a noncharacter.
    }; };

    using Display_width_details = variant<int, Special_display_widths::Enum>;

    extern auto monospaced_display_width_details_of( const char32_t code ) noexcept
        -> Display_width_details;

    inline auto monospaced_display_width_of_code( const char32_t code ) noexcept
        -> optional<int>
    {
        const auto w = monospaced_display_width_details_of( code );
        if( holds_alternative<int>( w ) ) { return get<int>( w ); } else { return {}; }
    }
        
    inline auto monospaced_display_width_of_text( in_<string_view> text ) noexcept
        -> optional<int>
    {
        int result = 0;
        for( in_<u8::Cp_bytes_ref> seq: u8::to_code_point_iterators( text ) ) {
            if( const auto w = monospaced_display_width_of_code( seq.as_number() ) ) {
                result += w.value();
            } else {
                return {};
            }
        }
        return result;
    }

    inline auto monospaced_display_width_of( const char32_t code ) noexcept
        -> optional<int>
    { return monospaced_display_width_of_code( code ); }

    inline auto monospaced_display_width_of( in_<string_view> text ) noexcept
        -> optional<int>
    { return monospaced_display_width_of_text( text ); }

    inline auto assumed_monospaced_display_width_of_code( const char32_t code ) noexcept
        -> int
    {
        const auto w = monospaced_display_width_details_of( code );
        if( holds_alternative<int>( w ) ) {
            return get<int>( w );
        }
        
        // Not unreasonable assumptions:
        switch( get<Special_display_widths::Enum>( w ) ) {
            case Special_display_widths::nonprint:          return 0;
            case Special_display_widths::combining:         return 0;
            case Special_display_widths::ambiguous:         return 1;
            case Special_display_widths::private_use:       return 1;
            case Special_display_widths::unassigned:        return 0;
            case Special_display_widths::non_character:     return 0;
            case Special_display_widths::widened_in_9:      return 2;
            default: {
                assert( false );
                for( ;; ) {}        // Should never get here.
            }
        }
    }

    inline auto assumed_monospaced_display_width_of_text( in_<string_view> text ) noexcept
        -> int
    {
        int result = 0;
        for( in_<u8::Cp_bytes_ref> seq: u8::to_code_point_iterators( text ) ) {
            result += assumed_monospaced_display_width_of_code( seq.as_number() );
        }
        return result;
    }

    inline auto assumed_monospaced_display_width_of( const char32_t code ) noexcept
        -> int
    { return assumed_monospaced_display_width_of_code( code ); }

    inline auto assumed_monospaced_display_width_of( in_<string_view> text ) noexcept
        -> int
    { return assumed_monospaced_display_width_of_text( text ); }

    namespace x = unicode;
    namespace exports { using
        x::Special_display_widths,
        x::Display_width_details,
            // optional<int> result:
        x::monospaced_display_width_details_of,
        x::monospaced_display_width_of_code,
        x::monospaced_display_width_of_text,
        x::monospaced_display_width_of,
            // int result (just a guesstimate when unknown):
        x::assumed_monospaced_display_width_of_code,
        x::assumed_monospaced_display_width_of_text,
        x::assumed_monospaced_display_width_of;
    }  // namespace exports
}  // namespace fsm_definitions::unicode

namespace fabulous_support_machinery{
    // `unicode::` stuff is intentionally not available unqualified in fsm namespace.
    
    // Not a simple equate because may need to be an extension of earlier declared namespace.
    namespace unicode{
        using namespace fsm_definitions::unicode::exports;
    }  // namespace unicode
}
