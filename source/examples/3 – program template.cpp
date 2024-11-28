// A general template for simple applications.
//
// The `app` namespace serves as container for the application logic, marking it as such.
// `fsm::with_exceptions_displayed` handles an exception with a stderr message and `EXIT_FAILURE` return.
//
#include <fsm/core.hpp>
#include <string>

namespace app {
    using   fsm::is_empty, fsm::input, fsm::put;    // Or just `using namespace fsm;`.
    using   std::string;

    void run()
    {
        const string username = input( "Hi, what’s your name? " );  // Trimmed by default.
        put( "Pleased to meet you, {}!\n", is_empty( username )? "ℕ.ℕ." : username );
    }
}  // namespace app

auto main() -> int { return fsm::with_exceptions_displayed( app::run ); }
