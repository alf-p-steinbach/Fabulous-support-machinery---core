#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/parameter_passing/in_.hpp>   // in_
#include <fsm/core/stream_io/put.hpp>           // put

#include <functional>
#include <stdexcept>

#include <fsm/core/wrapped/c_lib/stdlib.hpp>

namespace fsm_definitions {
    using   fsm::in_,                   // parameter_passing/in_
            fsm::put, fsm::put_to;      // stream_io/put

    using   std::function,              // <functional>
            std::exception;             // <stdexcept>

    namespace exception_handling {
        inline auto with_exceptions_displayed( in_<function<void()>> f )
            -> int
        {
            try{
                f();
                return EXIT_SUCCESS;
            } catch( in_<exception> x ) {
                put( "\n" );
                put_to( stderr, "!{}\n", x.what() );
            } catch( ... ) {
                put( "\n" );
                put_to( stderr, "!<unknown exception>\n" );
            }
            return EXIT_FAILURE;
        }
    }  // namespace exception_handling
}  // namespace fsm_definitions

namespace fsm {
    inline namespace exception_handling { using namespace fsm_definitions::exception_handling; }
}  // namespace fsm
