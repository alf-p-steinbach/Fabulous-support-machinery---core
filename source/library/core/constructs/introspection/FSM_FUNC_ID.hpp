#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/basic-types/Size+Index.hpp>                  // Index
#include <fsm/core/constructs/declarations/type_builders.hpp>   // in_

#include <string_view>

// Can't test directly for existence of the pseudo-macros, so must test compiler ids:
#if     defined( _MSC_VER )      // Visual C++
#   define FSM_FUNC_DECL                                    __FUNCSIG__
#elif   defined( __GNUC__ ) or defined( __clang__ )
#   define FSM_FUNC_DECL                                    __PRETTY_FUNCTION__
#else
#   define FSM_FUNC_DECL                                    __func__
#endif

#define FSM_FUNC_ID   fsm_definitions::func_id_from( FSM_FUNC_DECL )

namespace fsm_definitions {
    namespace fsm = fabulous_support_machinery;
    using   fsm::Index,
            fsm::in_;
    using   std::string_view;
    
    constexpr auto func_id_from( in_<string_view> func_decl )
        -> string_view
    {
        const auto i_parens = static_cast<Index>( func_decl.find( '(' ) );
        if( i_parens < 0 ) {
            return func_decl;       // Probably a `__func__` as argument.
        }
        const auto i_space = static_cast<Index>( func_decl.rfind( ' ', i_parens ) );
        const auto i_first = (i_space < 0? 0 : i_space + 1);
        return func_decl.substr( i_first, i_parens - i_first );
    }

}  // namespace fsm_definitions
