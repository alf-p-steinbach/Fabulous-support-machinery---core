#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/exception/types/Std_exception.hpp>                   // Std_exception
#include <fsm/core/parameter_passing/data_flow_directions.hpp>          // in_

#include <stdexcept>
#include <exception>
#include <optional>

namespace fsm_definitions {
    using   fsm::Std_exception,             // exception/types/Std_exception.hpp
            fsm::in_;                       // parameter_passing/in_.hpp

    using   std::exception_ptr, std::nested_exception, std::rethrow_exception,  // <exception>
            std::optional;                                                      // <optional>

    class Unpropagated_nested_exception:
        public Std_exception
    {
    public:
        auto what() const noexcept
            -> const char* override
        { return "A nested exception but without any info (its exception pointer was not propagated)."; } 
    };

    namespace exception { inline namespace throwing {
        inline auto is_unpropagated_nested_exception( in_<Std_exception> x )
            -> bool
        { return !!dynamic_cast<const Unpropagated_nested_exception*>( &x ); }

        inline auto nested_exception_if_any_in( in_<Std_exception> x )
            -> optional< exception_ptr >
        {
            if( const auto p_nest = dynamic_cast<const nested_exception*>( &x ) ) {
                return p_nest->nested_ptr();        // May be null for Homebrew g++ on the Mac.
            }
            return {};
        }

        // With Homebrew g++ on the Mac `std::rethrow_if_nested` just crashes in libc++. So:
        inline void rethrow_nested_if_any_in( in_<Std_exception> x )
        {
            if( const auto opt_ptr = nested_exception_if_any_in( x ) ) {
                if( not opt_ptr.value() ) {
                    throw Unpropagated_nested_exception();
                }
                rethrow_exception( opt_ptr.value() );
            }
        }
    } }  // namespace exception / inline namespace throwing
}  // namespace fsm_definitions

namespace fsm {
    inline namespace exception { using namespace fsm_definitions::exception; }
}  // namespace fsm
