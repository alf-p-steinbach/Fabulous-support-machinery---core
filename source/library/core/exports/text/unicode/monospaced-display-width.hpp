#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/text/encoding/u8/Code_point_iterator_.hpp>

#include <optional>
#include <string_view>
#include <variant>

namespace fabulous_support_machinery::unicode::_definitions {
    using   std::optional, std::holds_alternative, std::get,
            std::string_view,
            std::variant;

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
        for( in_<u8::Code_point_ref> seq: u8::to_code_point_iterators( text ) ) {
            if( const auto w = monospaced_display_width_of_code( seq.codepoint() ) ) {
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
                for( ;; ) {}        // Should never get here.
            }
        }
    }

    inline auto assumed_monospaced_display_width_of_text( in_<string_view> text ) noexcept
        -> int
    {
        int result = 0;
        for( in_<u8::Code_point_ref> seq: u8::to_code_point_iterators( text ) ) {
            result += assumed_monospaced_display_width_of_code( seq.codepoint() );
        }
        return result;
    }

    inline auto assumed_monospaced_display_width_of( const char32_t code ) noexcept
        -> int
    { return assumed_monospaced_display_width_of_code( code ); }

    inline auto assumed_monospaced_display_width_of( in_<string_view> text ) noexcept
        -> int
    { return assumed_monospaced_display_width_of_text( text ); }

    namespace d = _definitions;
    namespace exports { using
        d::Special_display_widths,
        d::Display_width_details,
        d::monospaced_display_width_details_of,
        d::monospaced_display_width_of_code,
        d::monospaced_display_width_of_text,
        d::monospaced_display_width_of,
        d::assumed_monospaced_display_width_of_code,
        d::assumed_monospaced_display_width_of_text,
        d::assumed_monospaced_display_width_of;
    }  // namespace exports
}  // namespace fabluous_support_machinery::unicode::_definitions

namespace fabulous_support_machinery::unicode  { using namespace _definitions::exports; }
