#include <fsm/_simple.hpp>

namespace app {
    using namespace fsm::namespace_names;   // console, u8, unicode, fmtlib
    constexpr auto text = "Every 日本国 кошка loves blåbærsyltetøy!"sv;

    void run()
    {
        // Just display the message.
        console::print_fmt( "{}\n", text );
        
        // Display one line for each code point with string index, symbol and code point value,
        // all nicely aligned vertically.
        for( const u8::Cp_bytes_ref cp_bytes: u8::Cp_sequence_view( text ) ) {
            const auto index = cp_bytes.char_pointer() - text.data();
            console::print_fmt( "{:2}: {:>6} {:>9}\n",
                index,                                      // Index in string.
                fmtlib::format( "‘{}’", cp_bytes.sv() ),    // E.g. "‘日’".
                unicode::to_spec( cp_bytes.as_number() )    // E.g. "u65E5".
                );
        }
    }
}  // namespace app

auto main() -> int { return fsm::with_xinfo_to_err_stream( app::run ); }
