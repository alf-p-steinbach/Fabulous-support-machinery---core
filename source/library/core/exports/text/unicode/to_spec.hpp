#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include    <string>        // std::string
#include    <stdio.h>       // sprintf

namespace fabulous_support_machinery::unicode::_definitions {
    using   std::string;            // <string>

    inline auto to_spec( const char32_t code )
        -> string
    {
        char result[16] = "u";
        sprintf( result + 1, "%0*X", (code > 0xFFFF? 8 : 4), static_cast<unsigned>( code ) );
        return result;
    }

    namespace d = _definitions;
    namespace exports { using
        d::to_spec;
    }  // namespace exports
}  // namespace fabluous_support_machinery::unicode::_definitions

namespace fabulous_support_machinery::unicode  { using namespace _definitions::exports; }
