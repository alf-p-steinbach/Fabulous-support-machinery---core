#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/constructs/introspection/exception_type_name_for.hpp>
#include <fsm/core/exception_handling/for_each_exception_in.hpp>            // for_each_exception_in
#include <fsm/core/parameter_passing/data_flow_directions.hpp>              // in_
#include <fsm/core/stream_io/output.hpp>                                    // output

#include <functional>
#include <stdexcept>

#include <fsm/core/wrapped/c_lib/stdlib.hpp>

namespace fsm_definitions {
    using   fsm::exception_type_name_for,
            fsm::in_,                   // parameter_passing/in_
            fsm::put_to;                // stream_io/put

    using   std::function,              // <functional>
            std::exception;             // <stdexcept>

    namespace exception_handling {
        inline auto with_exceptions_displayed( in_<function<void()>> f )
            -> int
        {
            const auto output_message = [&]( in_<exception> x )
            {
                put_to( stderr, "\n" ); // TODO: restrict to stdout = console
                // TODO: use named arguments? Problem: not in stdlib.
                for_each_exception_in( x, [&]( in_<exception> each ) {
                    put_to( stderr, "{}{} [{}]\n",
                        (&each == &x? "!" : "    because: "),
                        each.what(),
                        exception_type_name_for( each )
                        );
                } );
            };

            // TODO: common exception translation?
            try{
                f();
                return EXIT_SUCCESS;
            } catch( in_<exception> x ) {
                output_message( x );
            } catch( const C_str s ) {
                output_message( Basic_type_exception_<C_str>( s ) );
            } catch( const int v ) {
                output_message( Basic_type_exception_<int>( v ) );
            } catch( ... ) {
                put_to( stderr, "\n" ); // TODO: restrict to stdout = console
                put_to( stderr, "!<unknown exception>\n" );
            }
            return EXIT_FAILURE;
        }
    }  // namespace exception_handling
}  // namespace fsm_definitions

namespace fsm {
    inline namespace exception_handling { using namespace fsm_definitions::exception_handling; }
}  // namespace fsm
