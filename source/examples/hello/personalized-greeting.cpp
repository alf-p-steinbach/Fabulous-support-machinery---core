#include <fsm/text-io.hpp>
namespace fsm = fabulous_support_machinery;

#include <string>
#include <string_view>

namespace app {
    using namespace fsm::console;       // input, output
    using   std::string;
    using   Sv = std::string_view;
    using   fsm::is_empty;

    void run()
    {
        output( "An FSM-based simple personalized greeting program.\n" );
        output( "\n" );
        const string specified_name = input( "Hi, what’s your name? " );
        const Sv name = (is_empty( specified_name )? "<anonymous>" : Sv( specified_name ) );
        output( "Pleased to meet you, ", name, "!\n" );
    }
}  // namespace app

auto main() -> int { return fsm::with_xinfo_to_err_stream( app::run ); }
