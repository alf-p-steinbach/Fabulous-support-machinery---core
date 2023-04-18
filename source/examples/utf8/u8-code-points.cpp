#include <fsm/all.hpp>
#include <fsm/$-macros.hpp>     // $nsname_from
namespace fsm = fabulous_support_machinery;

#include <string_view>

namespace app {
    $nsname_from( fsm, console );  $nsname_from( fsm, u8 );  $nsname_from( fsm, unicode );

    void run()
    {
        constexpr auto text = "Every 日本国 кошка loves blåbærsyltetøy!"sv;

        // Just display the message.
        console::output( text, "\n" );

        // Display one line for each code point with string index, symbol and code point value,
        // all nicely aligned vertically.
        const auto u8_text = u8::Code_points_view( text );
        for( const u8::Code_point_ref seq: u8_text ) {
            const auto index = seq.char_pointer() - text.data();
            console::output(
                console::right( 2, index ), ": ",                                   // Index in string.
                console::right( 6, fsm::string_from( "‘", seq.sv(), "’" ) ), " ",   // E.g. "‘日’".
                console::right( 9, unicode::to_spec( seq.cp_number() ) ),           // E.g. "u65E5".
                "\n"
                );
        }
    }
}  // namespace app

auto main() -> int { return fsm::with_exception_info_to_stderr( app::run ); }
