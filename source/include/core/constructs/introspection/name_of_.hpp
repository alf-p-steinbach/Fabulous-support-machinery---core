#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/constructs/introspection/name_of_/raw_name_of_exactly_.hpp>
#include <fsm/core/constructs/introspection/name_of_//unmangled_and_cleaned_type_name_from.hpp>

#include <string>

namespace fsm_definitions {
    using   fsm::raw_name_of_exactly_,
            fsm::unmangled_and_cleaned_type_name_from;
    using   std::string;

    namespace introspection {

        template< class Type >
        auto name_of_()
            -> std::string
        { return unmangled_and_cleaned_type_name_from( raw_name_of_exactly_<Type>().c_str() ); }

    }  // namespace introspection
}  // namespace fsm_definitions

namespace fsm {
    inline namespace introspection { using namespace fsm_definitions::introspection; }
}  // namespace fsm
