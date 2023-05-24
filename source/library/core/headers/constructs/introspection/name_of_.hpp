#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/headers/+std-cpp-language.hpp>

#include <fsm/core/headers/constructs/introspection/raw_name_of_exactly_.hpp>
#include <fsm/core/headers/constructs/introspection/unmangled_and_cleaned_type_name.hpp>

#include <string>

namespace fabulous_support_machinery::_definitions {
    using   std::string;

    template< class Type >
    inline auto name_of_()
        -> std::string
    { return unmangled_and_cleaned_type_name( raw_name_of_exactly_<Type>() ); }

    namespace d = _definitions;
    namespace exports{ using
        d::name_of_;
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace _definitions::exports; }
