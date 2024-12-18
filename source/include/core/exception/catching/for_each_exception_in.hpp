#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/basic_type/names/C_str.hpp>                          // C_str
#include <fsm/core/constructs/introspection/name_of_.hpp>               // name_of_
#include <fsm/core/exception/throwing/rethrow_nested_if_any_in.hpp>     // rethrow_nested_if_any_in
#include <fsm/core/exception/types/Basic_type_exception_.hpp>           // Basic_type_exception_
#include <fsm/core/exception/types/Std_exception.hpp>                   // Std_exception
#include <fsm/core/exception/types/Unknown_exception.hpp>               // Unknown_exception
#include <fsm/core/parameter_passing/data_flow_directions.hpp>          // in_

#include <exception>
#include <functional>
#include <stdexcept>
#include <string>

namespace fsm_definitions {
    using   fsm::C_str,                         // basic_type/names/C_str
            fsm::name_of_,                      // constructs/introspection/name_of_
            fsm::rethrow_nested_if_any_in,      // exception/throwing/rethrow_nested_if_any_in
            fsm::Basic_type_exception_,         // exception/types/Basic_type_exception_
            fsm::Std_exception,                 // exception/types/Std_exception
            fsm::Unknown_exception,             // exception/types/Unknown_exception
            fsm::in_;                           // parameter_passing/data_flow_directions

    using   std::current_exception, std::exception_ptr, std::make_exception_ptr, std::rethrow_exception,    // <exception>
            std::function,                      // <functional>
            std::runtime_error,                 // <stdexcept>
            std::string,                        // <string>
            std::is_same_v;                     // <type_traits>

    namespace exception{ inline namespace catching{
        #if 0       // Iterative version.
            inline void rethrow_if_nested_pointee( in_<exception_ptr> p )
            {
                try {
                    rethrow_exception( p );
                } catch( in_<exception> x ) {
                    rethrow_nested_if_any_in( x );
                } catch( ... ) {
                    ;
                }
            }

            inline auto for_each_nested_exception_in(
                in_<Std_exception>                          final_x,
                in_<function<void( in_<Std_exception> )>>   f
                ) -> bool
            {
                exception_ptr p_current = nullptr;
                for( ;; ) {
                    try {
                        if( not p_current ) {
                            rethrow_nested_if_any_in( final_x );    // Rethrows a nested exception, if any.
                        } else {
                            rethrow_if_nested_pointee( p_current );
                        }
                        return true;
                    } catch( in_<Std_exception> x ) {
                        f( x );
                        p_current = current_exception();
                    } catch( ... ) {
                        f( Unknown_exception{ current_exception() } );
                        return false;
                    }
                }
            }
        #endif

        inline auto for_each_nested_exception_in(
            in_<Std_exception>                          x,
            in_<function<void( in_<Std_exception> )>>   f
            ) -> bool
        {
            const auto ff = [&f]( const auto& nested ) -> bool
            {
                f( nested ); return false;
            };

            try {
                rethrow_nested_if_any_in( x );
                return true;
            } catch( const C_str s ) {
                return ff( Basic_type_exception_<C_str>( s ) );
            } catch( in_<string> s ) {
                return ff( Basic_type_exception_<string>( s ) );
            } catch( const int v ) {
                return ff( Basic_type_exception_<int>( v ) );
            } catch( const double v ) {
                return ff( Basic_type_exception_<double>( v ) );
            } catch( in_<Std_exception> nested_x ) {
                f( nested_x );
                return for_each_nested_exception_in( nested_x, f );
            } catch( ... ) {
                return ff( Unknown_exception{ current_exception() } );
            }
            for( ;; ) {}        // Should never get here.
        }

        inline auto for_each_exception_in(
            in_<Std_exception>                          final_x,
            in_<function<void( in_<Std_exception> )>>   f
            ) -> bool
        {
            f( final_x );
            return for_each_nested_exception_in( final_x, f );
        }
    } }  // namespace exception_handling / inline namespace catching
}  // namespace fsm_definitions

namespace fsm {
    inline namespace exception { using namespace fsm_definitions::exception; }
}  // namespace fsm
