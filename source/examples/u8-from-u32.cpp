#include <fsm/core.hpp>
#include <string>
#include <string_view>

#define CONCAT_( a, b)   a ## b
#define CONCAT( a, b)    CONCAT_( a, b )

#define S       "Grønn 日本国";
#define S32     CONCAT( U, S )

namespace app {
    $nsname_from( fsm, u8 );
    using   fsm::Byte, fsm::Nat, fsm::format, fsm::put;
    using   std::string, std::string_view, std::u32string_view;

    void run()
    {
        constexpr string_view       text    = S;
        constexpr u32string_view    text32  = S32;

        bool buggy = false;
        const char* p = text.data();
        for( const char32_t code: text32 ) {
            put( "{:>5}:  ", format( "'{}'", string_view( p, +u8::seq_length_of( *p ) ) ) );

            const auto correct_seq = string_view( p, +u8::seq_length_of( *p ) );
            for( const Byte u8_code: correct_seq ) {
                put( "{:0>2X} ", u8_code );
            }
            put( "| " );

            char bytes[4];
            const Nat length = u8::to_seq_at( bytes, code );
            const auto generated_seq = string_view( bytes, +length );
            for( const Byte u8_code: generated_seq ) {
                put( "{:0>2X} ", u8_code );
            }

            if( correct_seq != generated_seq ) {
                put( "  <-- !Bug here." );
                buggy = true;
            }
            put( "\n" );

            p += +u8::seq_length_of( *p );
        }
        put( "{}\n", buggy? "One or more bugs detected. :(" : "All OK." );
    }
}  // namespace app

auto main() -> int { return fsm::with_exceptions_displayed( app::run ); }
