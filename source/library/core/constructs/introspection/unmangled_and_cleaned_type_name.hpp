#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/constructs/declarations/type_builders.hpp>     // in_

#include <string>
#include <string_view>

namespace fsm_definitions {
    namespace fsm = fabulous_support_machinery;
    using   fsm::in_;
    using   std::string,            // <string>
            std::string_view;       // <string_view>
    
    extern auto unmangled_and_cleaned_type_name( in_<string_view> builtin_type_name )
        -> string;

    namespace d = fsm_definitions;
    namespace exports{ using
        d::unmangled_and_cleaned_type_name;
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace fsm_definitions::exports; }
