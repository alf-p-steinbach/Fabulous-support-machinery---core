#include <fsm/core.hpp>

namespace app {
    using   fsm::is_empty, fsm::input_line, fsm::put;   // Or just `using namespace fsm;`.
    using   std::string;

    void run()
    {
        const char32_t code = {};
        put( "char32_t  = {} .\n", typeid( code ).name() );
        put( "+char32_t = {} .\n", typeid( +code ).name() );
    }
}  // namespace app

auto main() -> int { return fsm::with_exceptions_displayed( app::run ); }
