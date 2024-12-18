#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/basic_type/names/C_str.hpp>                          // C_str
#include <fsm/core/constructs/introspection/name_of_.hpp>               // name_of_
#include <fsm/core/parameter_passing/data_flow_directions.hpp>          // in_

#include <stdexcept>
#include <type_traits>

namespace fsm_definitions {
    using   fsm::C_str,                         // basic_type/names/C_str
            fsm::name_of_,                      // constructs/introspection/name_of_
            fsm::in_;                           // parameter_passing/data_flow_directions

    using   std::runtime_error,                 // <stdexcept>
            std::string,                        // <string>
            std::is_same_v;                     // <type_traits>

    namespace exception { inline namespace types {

        template< class Basic_type >
        class Basic_type_exception_:
            public runtime_error
        {
        public:
            static constexpr bool is_string = (is_same_v<Basic_type, C_str> or is_same_v<Basic_type, string>);

        private:
            Basic_type      m_value;

            static auto description_of( in_<Basic_type> v )
                -> string
            {
                if constexpr( is_string ) {
                    return v;
                } else {
                    return format( "<exception of type {} with value {}>", name_of_<Basic_type>(), v );
                }
            }

        public:
            Basic_type_exception_( in_<Basic_type> v ):
                runtime_error( description_of( v ) ),
                m_value( v )
            {}

            auto value() const -> Basic_type { return m_value; }
        };

    } }  // namespace exception / inline namespace types
}  // namespace fsm_definitions

namespace fsm {
    inline namespace exception { using namespace fsm_definitions::exception; }
}  // namespace fsm
