#include <fsm/_simple.hpp>

namespace app {
    using namespace fsm::namespace_names;   // console, u8, unicode
    constexpr auto text = "Every 日本国 кошка loves blåbærsyltetøy!"sv;

    void run()
    {
        // Just display the message.
        console::output( text, "\n" );

        // Display one line for each code point with string index, symbol and code point value,
        // all nicely aligned vertically.
        const auto u8_code_points = u8::Cp_sequence_view( text );
        for( const u8::Cp_bytes_ref cp_bytes: u8_code_points ) {
            const auto index = cp_bytes.char_pointer() - text.data();
            console::output(
                console::right( 2, index ), ": ",                                       // Index in string.
                console::right( 6, fsm::string_from( "‘", cp_bytes.sv(), "’" ) ), " ",  // E.g. "‘日’".
                console::right( 9, unicode::to_spec( cp_bytes.as_number() ) ),          // E.g. "u65E5".
                "\n"
                );
        }
    }
}  // namespace app

auto main() -> int { return fsm::with_xinfo_to_err_stream( app::run ); }
