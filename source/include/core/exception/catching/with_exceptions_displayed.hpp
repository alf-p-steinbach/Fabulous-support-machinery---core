#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/constructs/introspection/exception_type_name_for.hpp>    // exception_type_name_for
#include <fsm/core/exception/catching/for_each_exception_in.hpp>            // for_each_exception_in
#include <fsm/core/exception/types/Std_exception.hpp>                       // Std_exception
#include <fsm/core/parameter_passing/data_flow_directions.hpp>              // in_
#include <fsm/core/stream_io/output.hpp>                                    // output

#include <functional>
#include <stdexcept>

#include <fsm/core/wrapped/c_lib/stdlib.hpp>

namespace fsm_definitions {
    using   fsm::exception_type_name_for,   // constructs/introspection/exception_type_name_for
            fsm::for_each_exception_in,     // exception/catching/for_each_exception_in
            fsm::Std_exception,             // exception/types/Std_exception
            fsm::in_,                       // parameter_passing/data_flow_directions
            fsm::put_to;                    // stream_io/output

    using   std::function;                  // <functional>

    namespace exception { inline namespace catching {
        inline auto with_exceptions_displayed( in_<function<void()>> f )
            -> int
        {
            const auto output_message = [&]( in_<Std_exception> x )
            {
                put_to( stderr, "\n" ); // TODO: restrict to stdout = console
                // TODO: use named arguments? Problem: not in stdlib.
                for_each_exception_in( x, [&]( in_<Std_exception> each ) {
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
            } catch( const C_str s ) {
                output_message( Basic_type_exception_<C_str>( s ) );
            } catch( const int v ) {
                output_message( Basic_type_exception_<int>( v ) );
            } catch( const double v ) {
                output_message( Basic_type_exception_<double>( v ) );
            } catch( in_<Std_exception> x ) {
                output_message( x );
            } catch( ... ) {
                put_to( stderr, "\n" ); // TODO: restrict to stdout = console
                put_to( stderr, "!<unknown exception>\n" );
            }
            return EXIT_FAILURE;
        }
    } }  // namespace exception_handling / inline namespace catching
}  // namespace fsm_definitions

namespace fsm {
    inline namespace exception { using namespace fsm_definitions::exception; }
}  // namespace fsm
