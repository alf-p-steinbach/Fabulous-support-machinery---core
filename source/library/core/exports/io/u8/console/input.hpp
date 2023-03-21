#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <string>

namespace fabulous_support_machinery::console::_definitions {
    using   std::string;            // <string>

    extern auto input_using_buffer( string&& buffer ) -> string;

    inline auto input()
        -> string
    { return input_using_buffer( "" ); }

    namespace d = _definitions;
    namespace exports{ using
        d::input_using_buffer, d::input;
    }  // namespace exports
}  // namespace fabulous_support_machinery::console::_definitions

namespace fabulous_support_machinery::console   { using namespace _definitions::exports; }
