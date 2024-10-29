#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/type_builders.hpp>       // in_
#include <fsm/core/constructs/introspection/name_of_/unmangled_and_cleaned_type_name_from.hpp>

#include <string>
#include <typeindex>
#include <typeinfo>

namespace fsm_definitions {
    using   fsm::in_,
            fsm::unmangled_and_cleaned_type_name_from;
    using   std::string,            // <string>
            std::type_index,        // <typeindex>
            std::type_info;         // <type_info>

    namespace introspection {

        inline auto name_of( in_<type_index> info )
            -> string
        { return unmangled_and_cleaned_type_name_from( info.name() ); }

        inline auto name_of( in_<type_info> info )
            -> string
        { return unmangled_and_cleaned_type_name_from( info.name() ); }

    }  // namespace introspection
}  // namespace fsm_definitions

namespace fsm {
    inline namespace introspection { using namespace fsm_definitions::introspection; }
}  // namespace fsm
