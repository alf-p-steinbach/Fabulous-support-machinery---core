#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/constructs/introspection/raw_name_of_exactly_.hpp>
#include <fsm/core/constructs/introspection/unmangled_and_cleaned_type_name.hpp>

#include <string>

namespace fsm_definitions {
    namespace fsm = fabulous_support_machinery;
    using   fsm::raw_name_of_exactly_,
            fsm::unmangled_and_cleaned_type_name;
    using   std::string;

    template< class Type >
    inline auto name_of_()
        -> std::string
    { return unmangled_and_cleaned_type_name( raw_name_of_exactly_<Type>() ); }

    namespace d = fsm_definitions;
    namespace exports{ using
        d::name_of_;
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace fsm_definitions::exports; }
