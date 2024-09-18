#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <fsm/core/parameter_passing.hpp>       // Moving_, in_

#include <stdexcept>
#include <string>

namespace fsm_definitions {
    using   fsm::Moving_, fsm::in_;
    using   std::runtime_error,             // <stdexcept>
            std::string;                    // <string>

    namespace exception_handling
    {

        constexpr auto now( const bool condition ) noexcept -> bool { return condition; }
        
        template< class X, class... Args >
        [[noreturn]]
        auto fail_( Moving_<string> message, in_<Args>... args )
            -> bool
        {
            throw X( message, args... );
            for( ;; ) {}        // Should never get here.
        }

        [[noreturn]]
        inline auto fail( Moving_<string> message )
            -> bool
        {
            fail_<runtime_error>( message );
            for( ;; ) {}        // Should never get here.
        }

    }
}  // namespace fsm_definitions

namespace fsm {
    inline namespace exception_handling {
        using namespace fsm_definitions::exception_handling;
    }
}  // namespace fsm
