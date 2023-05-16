// Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/text/unicode/monospaced-display-width.hpp>

#include <fsm/@wrapped/3rd-party-lib/widechar_wcwidth/exports/all.hpp>

namespace fsm_definitions::unicode {

    /*   // For exposition:
        using   std::variant;

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
    */

    auto monospaced_display_width_details_of( const char32_t code ) noexcept
        -> Display_width_details
    {
        // Heuristic:
        // { return 1 + (code >= 0x1100); }

        // More reliable but subject to inconsistency with at any time latest Unicode standard:
        const int w = ::widechar_wcwidth( code );
        return (w >= 0
            ? Display_width_details( w )
            : Display_width_details( Special_display_widths::Enum( w ) )
            );
    }
}  // namespace fsm_definitions::unicode
