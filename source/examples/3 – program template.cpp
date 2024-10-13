// A general template for simple applications.
//
#include <fsm/core.hpp>
#include <string>

namespace app {
    using   fsm::put, fsm::trimmed, fsm::input_line;    // Or just `using namespace fsm;`.
    using   std::string;

    void run()
    {
        const string username = input_line( "Hi, what’s your name? " ); // Trimmed by default.
        put( "Pleased to meet you, {}!\n", username.empty()? "ℕ.ℕ." : username );
    }
}  // namespace app

// An input stream exception, e.g. EOF, is handled with a stderr message and failure exit code.
auto main() -> int { return fsm::with_exceptions_displayed( app::run ); }
