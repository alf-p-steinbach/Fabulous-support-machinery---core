#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/constructs/introspection/name_of.hpp>        // name_of
#include <fsm/core/exception/types/Std_exception.hpp>           // Std_exception
#include <fsm/core/type_builders.hpp>                           // in_

#include <exception>
#include <stdexcept>
#include <string>

namespace fsm_definitions {
    using   fsm::name_of,               // constructs/introspection/name_of
            fsm::Std_exception,         // exception/types/Std_exception
            fsm::in_;                   // parameter_passing/in_

    using   std::nested_exception,      // <exception>
            std::string;                // <string>

    namespace introspection {

        inline auto exception_type_name_for( in_<Std_exception> x, const bool add_nesting_indicator = true )
            -> string
        {
            const string raw_name = name_of( typeid( x ) );
            const bool has_nested_x = !!dynamic_cast<const nested_exception*>( &x );
            if( has_nested_x ) {
                const size_t    i_first     = raw_name.find_first_of( '<' ) + 1;
                const size_t    i_beyond    = raw_name.find_last_of( '>' );
                const auto      npos        = size_t( -1 );

                if( i_first != npos and i_beyond != npos ) {
                    const auto nesting_indicator = (add_nesting_indicator? "+" : "");
                    return raw_name.substr( i_first, i_beyond - i_first ) + nesting_indicator;
                }
            }
            return raw_name;
        }

    }  // namespace introspection
}  // namespace fsm_definitions

namespace fsm {
    inline namespace introspection { using namespace fsm_definitions::introspection; }
}  // namespace fsm
