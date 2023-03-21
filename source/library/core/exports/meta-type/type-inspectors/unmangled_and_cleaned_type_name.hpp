#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/type_builders.hpp>     // in_

#include <string_view>

namespace fabulous_support_machinery::_definitions {
    using   std::string_view;
    
    extern auto unmangled_and_cleaned_type_name( in_<string_view> builtin_type_name )
        -> string;

    namespace d = _definitions;
    namespace exports{ using
        d::unmangled_and_cleaned_type_name;
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace _definitions::exports; }
