#include <fsm/core.hpp>

namespace app {
    void fundamental_operation() { $fail( "Gah, unable to do it." ); }

    void intermediate()
    {
        try{
            fundamental_operation();
        } catch( ... ) {
            $fail( "Passing the buck." );
        }
    }

    void top_level()
    {
        try{
            intermediate();
        } catch( ... ) {
            $fail( "I simply give up on this." );
        }
    }
}  // namespace app

auto main() -> int { return fsm::with_exceptions_displayed( app::top_level ); }
