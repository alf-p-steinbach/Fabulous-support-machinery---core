#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/basic_type/names/Index-and-Size.hpp>     // Index
#include <fsm/core/type_builders.hpp>                       // in_

#include <string_view>

namespace fsm_definitions {
    using   fsm::Index,                     // <basic_types/Index-and-Size.hpp>
            fsm::in_;                       // <type_builders.hpp>
    using   std::string_view;               // <string_view>

    // Qualified function name, if available.
    //
    // Assumes:
    // • Classic C function declaration syntax.
    // • No left parenthesis in return type specification.
    //
    // TODO: get rid of that last assumption.
    // TODO: add template args to name (different data with g++, clang and MSVC).

    constexpr auto funcname_from_raw_decl( in_<string_view> raw_func_decl )
        -> string_view
    {
        const auto i_parens = static_cast<Index>( raw_func_decl.find( '(' ) );
        if( i_parens < 0 ) {
            return raw_func_decl;       // Probably a `__func__` as argument.
        }
        const auto i_space = static_cast<Index>( raw_func_decl.rfind( ' ', i_parens ) );
        const auto i_first = (i_space < 0? 0 : i_space + 1);
        return raw_func_decl.substr( i_first, i_parens - i_first );
    }
}  // namespace fsm_definitions
