#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/headers/+std-cpp-language.hpp>

#include <fsm/core/headers/constructs/introspection/name_of_.hpp>

#include <string>
#include <string_view>

namespace fabulous_support_machinery::x::_definitions {
    using   std::string,            // <string>
            std::string_view;       // <string_view>
    
    template< class X >
    auto default_message_for_()
        -> string_view
    {
        static const string msg = name_of_<X>();
        return msg;
    }

    namespace d = _definitions;
    namespace exports { using d::default_message_for_; }
}  // namespace fabulous_support_machinery::x::_definitions

namespace fabulous_support_machinery::x     { using namespace _definitions::exports; }
