// A general template for simple applications.
// An exception (e.g. reading beyond EOF) is handled with a stderr message and failure exit code.
//
#include <fsm/core.hpp>
#include <string>

namespace app {
    using namespace fsm::bit_operations;    // Bitpattern_
    using   fsm::Byte, fsm::put;            // Or just `using namespace fsm;`.
    using   std::string;

    void run()
    {
        constexpr auto pattern = Bitpattern_<Byte>( "0101'00x1" );

        put( "Pattern: {}.\n", pattern.str() );
        put( "\n" );
        for( unsigned u = 0; u <= 0xFF; ++u ) {
            if( pattern.matches( Byte( u ) ) ) {
                put( "Match:   {:08b}.\n", u );
            }
        }
    }
}  // namespace app

auto main() -> int { return fsm::with_exceptions_displayed( app::run ); }
