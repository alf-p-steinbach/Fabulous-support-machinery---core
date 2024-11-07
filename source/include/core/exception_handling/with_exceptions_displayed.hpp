#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/constructs/introspection/exception_type_name_for.hpp>
#include <fsm/core/exception_handling/for_each_exception_in.hpp>            // for_each_exception_in
#include <fsm/core/parameter_passing/data_flow_directions.hpp>              // in_
#include <fsm/core/stream_io/put.hpp>                                       // put

#include <functional>
#include <stdexcept>

#include <fsm/core/wrapped/c_lib/stdlib.hpp>

namespace fsm_definitions {
    using   fsm::exception_type_name_for,
            fsm::in_,                   // parameter_passing/in_
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
            } catch( in_<exception> x0 ) {
                put( "\n" );    // TODO: restrict to stdout = console
                for_each_exception_in( x0, [&]( in_<exception> x ) {
                    put_to( stderr, "{}{} [{}]\n",
                        (&x == &x0? "!" : "    because: "), x.what(), exception_type_name_for( x )
                        );
                } );
            } catch( ... ) {
                put( "\n" );    // TODO: restrict to stdout = console
                put_to( stderr, "!<unknown exception>\n" );
            }
            return EXIT_FAILURE;
        }
    }  // namespace exception_handling
}  // namespace fsm_definitions

namespace fsm {
    inline namespace exception_handling { using namespace fsm_definitions::exception_handling; }
}  // namespace fsm
