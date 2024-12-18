// A general template for simple applications.
// The `app` namespace serves as container for the application specific logic, marking it as such.

#include <fsm/core.hpp>
#include <string>

namespace app {
    using   fsm::is_empty, fsm::input, fsm::output;
    using   std::string;

    void run()
    {
        const string username = input( "Hi, what’s your name? " );  // Trimmed by default.
        output( "Pleased to meet you, {}!\n", is_empty( username )? "ℕ.ℕ." : username );
        throw 3.14;
    }
}  // namespace app

// If exception: `with_exceptions_displayed` sends its message to stderr and returns `EXIT_FAILURE`.
// A best effort is made to also output messages of nested exceptions, but g++ on a Mac has a bug.
auto main() -> int { return fsm::with_exceptions_displayed( app::run ); }
