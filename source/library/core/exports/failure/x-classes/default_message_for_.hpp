#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/introspection/name_of_.hpp>

#include <string>

namespace fabulous_support_machinery::x::_definitions {
    using   std::string;            // <string>
    
    template< class X >
    auto default_message_for_() -> string { return name_of_<X>(); }

    namespace d = _definitions;
    namespace exports { using d::default_message_for_; }
}  // namespace fabulous_support_machinery::x::_definitions

namespace fabulous_support_machinery::x     { using namespace _definitions::exports; }
