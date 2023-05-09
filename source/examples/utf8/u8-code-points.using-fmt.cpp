#include <fsm/_all.hpp>
#include <fsm/$-macros.hpp>     // $nsname_from
namespace fsm = fabulous_support_machinery;

#include <string_view>

namespace app {
    $nsname_from( fsm, console );  $nsname_from( fsm, u8 );  $nsname_from( fsm, unicode );
    $nsname_from( fsm, fmtlib );

    void run()
    {
        constexpr auto text = "Every 日本国 кошка loves blåbærsyltetøy!"sv;

        // Just display the message.
        console::print_fmt( "{}\n", text );
        
        // Display one line for each code point with string index, symbol and code point value,
        // all nicely aligned vertically.
        const auto u8_code_points = u8::Code_points_view( text );
        for( const u8::Code_point_ref seq: u8_code_points ) {
            const auto index = seq.char_pointer() - text.data();
            console::print_fmt( "{:2}: {:>6} {:>9}\n",
                index,                                  // Index in string.
                fmtlib::format( "‘{}’", seq.sv() ),     // E.g. "‘日’".
                unicode::to_spec( seq.cp_number() )     // E.g. "u65E5".
                );
        }
    }
}  // namespace app

auto main() -> int { return fsm::with_xinfo_to_err_stream( app::run ); }
