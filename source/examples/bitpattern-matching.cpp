// A general template for simple applications.
// An exception (e.g. reading beyond EOF) is handled with a stderr message and failure exit code.
//
#include <fsm/core.hpp>
#include <string>

namespace app {
    using   fsm::input_line, fsm::put, fsm::trimmed;    // Or just `using namespace fsm;`.
    using   std::string;

    void run()
    {
    }
}  // namespace app

auto main() -> int { return fsm::with_exceptions_displayed( app::run ); }
