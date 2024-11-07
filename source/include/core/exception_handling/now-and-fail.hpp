#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/parameter_passing/data_flow_directions.hpp>      // in_

#include <exception>
#include <stdexcept>
#include <string>
#include <utility>

namespace fsm_definitions {
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

        [[noreturn]]
        inline auto fail( in_<string> message )
            -> bool
        {
            fail_<runtime_error>( message );
            for( ;; ) {}        // Should never get here.
        }
    }
}  // namespace fsm_definitions

namespace fsm {
    inline namespace exception_handling { using namespace fsm_definitions::exception_handling; }
}  // namespace fsm
