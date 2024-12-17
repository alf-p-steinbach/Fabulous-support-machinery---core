#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/parameter_passing/data_flow_directions.hpp>      // in_
#include <fsm/core/wrapped/fmt_lib/core.hpp>                        // fsm::fmt_lib::*

#include <exception>
#include <stdexcept>
#include <string>
#include <utility>

namespace fsm_definitions {
    namespace ff = fsm::fmt_lib;
    using   ff::format_string, ff::format;
    using   fsm::in_;
    using   std::current_exception, std::throw_with_nested,     // <exception>
            std::runtime_error,                                 // <stdexcept>
            std::string,                                        // <string>
            std::forward;                                       // <utility>

    namespace exception_handling
    {
        constexpr auto now( const bool condition ) noexcept -> bool { return condition; }
        
        template< class X, class... Args >
        [[noreturn]]
        inline auto fail_( in_<string> message, Args&&... args )
            -> bool
        {
            const bool has_current_exception = !!current_exception();
            if( has_current_exception ) {
                throw_with_nested( X( message, forward<Args>( args )... ) );
            } else {
                throw X( message, forward<Args>( args )... );
            }
            for( ;; ) {}        // Should never get here.
        }

        // TODO: consider removing this convenience overload.
        [[noreturn]]
        inline auto fail( in_<string> message )
            -> bool
        {
            fail_<runtime_error>( message );
            for( ;; ) {}        // Should never get here.
        }

        // template< class... Args >
        // [[noreturn]]
        // inline auto fail( in_<format_string<Args...> message_format, Args&&... args )
        //     -> bool
        // {
        //     fail_<runtime_error>( format( message_format, forward<Args>( args )... ) );
        //     for( ;; ) {}        // Should never get here.
        // }

    }
}  // namespace fsm_definitions

namespace fsm {
    inline namespace exception_handling { using namespace fsm_definitions::exception_handling; }
}  // namespace fsm
