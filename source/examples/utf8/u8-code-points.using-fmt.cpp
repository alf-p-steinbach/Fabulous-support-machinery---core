#include <fsm/all.hpp>
namespace fsm = fabulous_support_machinery;

#include <string>
#include <string_view>

namespace app {
    using namespace fsm::console::useful_ns_names;      // console, fmtlib, u8, unicode
    using   console::clear_screen, console::print, fmtlib::format, unicode::to_spec;

    void run()
    {
        clear_screen();
        constexpr auto text = "Every 日本国 кошка loves blåbærsyltetøy!"sv;

        // Just display the message.
        print( "{}\n", text );
        
        // Display one line for each code point with string index, symbol and code point value.
        for( const auto code_point: u8::Code_points_view( text ) ) {
            const auto index = code_point.char_pointer() - text.data();
            print( "{:2}: {:>6} {:>9}\n",
                index,                                  // Index in string.
                format( "‘{}’", code_point.sv() ),      // E.g. "‘日’".
                to_spec( code_point.codepoint() )       // E.g. "u65E5".
                );
        }
    }
}  // namespace app

auto main() -> int { return fsm::with_exception_info_to_stderr( app::run ); }
