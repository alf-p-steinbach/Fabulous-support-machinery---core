#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/basic_type/names/C_str.hpp>                      // C_str
#include <fsm/core/platform/inspection/os_id_macros.hpp>            // FMS_
#include <fsm/core/parameter_passing/data_flow_directions.hpp>      // in_

#include <string>
#include <string_view>

#include <cstdlib>

#ifdef  __GNUC__
#   include <cxxabi.h>
#endif

namespace fsm_definitions {
    using   fsm::in_;
    using   std::string,            // <string>
            std::string_view;       // <string_view>
    using   std::free;              // <cstdlib>

    #ifdef  __GNUC__
        // <url: https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.0/namespaceabi.html>
        using   abi::__cxa_demangle;
    #endif

    namespace introspection {
        #ifdef FSM_OS_IS_WINDOWS
            // TODO:
            extern auto unmangled_and_cleaned_type_name_from( const C_str builtin_type_name )
                -> string;
        #else
            inline auto unmangled_and_cleaned_type_name_from( const C_str builtin_type_name )
                -> string
            {
                struct Name
                {
                    char*   p   = nullptr;
                    ~Name() { if( p ) { free( p ); } }
                };

                int status = 0;
                // status 	*status is set to one of the following values:
                //
                // 0: The demangling operation succeeded.
                // -1: A memory allocation failure occurred.
                // -2: mangled_name is not a valid name under the C++ ABI mangling rules.
                // -3: One of the arguments is invalid.

                const Name name = { __cxa_demangle( builtin_type_name, {}, {}, &status ) };
                return (name.p? name.p : builtin_type_name);
            }
        #endif
    }  // namespace introspection
}  // namespace fsm_definitions

namespace fsm {
    inline namespace introspection { using namespace fsm_definitions::introspection; }
}  // namespace fsm
