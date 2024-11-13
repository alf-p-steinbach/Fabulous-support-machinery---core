#include <fsm/core.hpp>
#include <string_view>

namespace app {
    $nsname_from( fsm, u8 );
    using   fsm::const_, fsm::in_, fsm::put;
    using   std::string_view;

    void run()
    {
        constexpr string_view lines[] = { "Every 日本国 кошка", "loves blåbærsyltetøy!" };
        for( in_<string_view> s: lines ) {
            if( &s != &lines[0] ) { put( "\n" ); }

            const_<const char*> p_end = s.data() + s.length();

            // Display the characters.
            for( const char* p = s.data(); p != p_end; u8::move_to_next( p ) ) {
                put( "{:>5s}", string_view( p, u8::seq_length_of( *p ) ) );
            }
            put( "\n" );

            // Display the codes.
            for( const char* p = s.data(); p != p_end;  u8::move_to_next( p ) ) {
                put( " {:04X}", unsigned( u8::codepoint_from( p ) ) );
            }
            put( "\n" );
        }
    }
}  // namespace app

auto main() -> int { return fsm::with_exceptions_displayed( app::run ); }
