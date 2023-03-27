#include <fsm/all.hpp>
namespace fsm = fabulous_support_machinery;
#define NS FSM_USING_NSNAME

#include <string_view>

namespace app {
    NS( fsm, console );  NS( fsm, u8 );  NS( fsm, unicode );  NS( fsm, fmtlib );

    void run()
    {
        constexpr auto text = "Every 日本国 кошка loves blåbærsyltetøy!"sv;

        // Just display the message.
        console::clear_screen();
        console::print( "{}\n", text );
        
        // Display one line for each code point with string index, symbol and code point value.
        const auto u8_text = u8::Code_points_view( text );
        for( const u8::Code_point_ref seq: u8_text ) {
            const auto index = seq.char_pointer() - text.data();
            console::print( "{:2}: {:>6} {:>9}\n",
                index,                                  // Index in string.
                fmtlib::format( "‘{}’", seq.sv() ),     // E.g. "‘日’".
                unicode::to_spec( seq.cp_number() )     // E.g. "u65E5".
                );
        }
    }
}  // namespace app

auto main() -> int { return fsm::with_exception_info_to_stderr( app::run ); }
