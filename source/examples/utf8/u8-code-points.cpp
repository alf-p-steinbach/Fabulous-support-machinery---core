#include <fsm/core.hpp>
namespace fsm = fabulous_support_machinery;

#include <string>
#include <string_view>

namespace app {
    using namespace fsm::string_building;               // "<<" on strings.
    using namespace fsm::console::useful_ns_names;      // console, u8, unicode
    using   console::clear_screen, console::output, console::right, unicode::to_spec;

    void run()
    {
        clear_screen();
        constexpr auto text = "Every 日本国 кошка loves blåbærsyltetøy!"sv;

        // Just display the message.
        output( ""s << text << "\n" );

        // Display one line for each code point with string index, symbol and code point value.
        for( const auto code_point: u8::Code_points_view( text ) ) {
            output( ""s
                << right( 2, code_point.char_pointer() - text.data() ) << ": "
                << right( 6, ""s << "‘" << code_point.sv() << "’" ) << " "
                << right( 9, to_spec( code_point.codepoint() ) )
                << "\n"
                );
        }
    }
}  // namespace app

auto main() -> int { return fsm::with_exceptions_displayed( app::run ); }
