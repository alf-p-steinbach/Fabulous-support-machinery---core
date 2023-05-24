#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/headers/+std-cpp-language.hpp>

#include    <string>        // std::string
#include    <stdio.h>       // sprintf

namespace fsm_definitions::unicode {
    using   std::string;            // <string>

    inline auto to_spec( const char32_t code )
        -> string
    {
        char result[16] = "u";
        sprintf( result + 1, "%0*X", (code > 0xFFFF? 8 : 4), static_cast<unsigned>( code ) );
        return result;
    }
}  // namespace fsm_definitions::unicode

namespace fabulous_support_machinery{
    // `to_spec` is intentionally not available unqualified in the fsm namespace.
    
    // Not a simple equate because may need to be an extension of earlier declared namespace.
    namespace unicode{
        using fsm_definitions::unicode::to_spec;
    }  // namespace unicode
}  // namespace fabulous_support_machinery
