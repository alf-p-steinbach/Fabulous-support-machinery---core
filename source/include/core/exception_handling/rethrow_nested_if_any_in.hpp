#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/parameter_passing/data_flow_directions.hpp>          // in_

#include <exception>
#include <optional>
#include <stdexcept>

namespace fsm_definitions {
    using   fsm::in_;                   // parameter_passing/in_
    using   std::exception_ptr, std::nested_exception, std::rethrow_exception,  // <exception>
            std::optional,              // <optional>
            std::exception;             // <stdexcept>

    namespace exception_handling {

        class Unknown_nested_exception:
            public exception
        {
        public:
            auto what() const noexcept
                -> const char* override
            { return "A nested exception but without any info (exception pointer was not propagated)."; } 
        };

        inline auto nested_exception_if_any_in( const exception& x )
            -> optional< exception_ptr >
        {
            if( const auto p_nest = dynamic_cast<const nested_exception*>( &x ) ) {
                return p_nest->nested_ptr();        // May be null for Homebrew g++ on the Mac.
            }
            return {};
        }

        // With Homebrew g++ on the Mac `std::rethrow_if_nested` just crashes in libc++. So:
        inline void rethrow_nested_if_any_in( const exception& x )
        {
            if( const auto opt_ptr = nested_exception_if_any_in( x ) ) {
                if( not opt_ptr.value() ) {
                    throw Unknown_nested_exception();
                }
                rethrow_exception( opt_ptr.value() );
            }
        }

    }  // namespace exception_handling
}  // namespace fsm_definitions

namespace fsm {
    inline namespace exception_handling { using namespace fsm_definitions::exception_handling; }
}  // namespace fsm
