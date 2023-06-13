#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/constructs/declarations/type_builders.hpp>     // in_
#include <fsm/core/constructs/introspection/unmangled_and_cleaned_type_name.hpp>

#include <string>
#include <typeindex>
#include <typeinfo>

namespace fabulous_support_machinery::_definitions {
    using   std::string,            // <string>
            std::type_index,        // <typeindex>
            std::type_info;         // <type_info>
    
    inline auto name_of( in_<type_index> info )
        -> string
    { return unmangled_and_cleaned_type_name( info.name() ); }

    inline auto name_of( in_<type_info> info )
        -> string
    { return unmangled_and_cleaned_type_name( info.name() ); }

    namespace d = _definitions;
    namespace exports{ using
        d::name_of;
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace _definitions::exports; }
