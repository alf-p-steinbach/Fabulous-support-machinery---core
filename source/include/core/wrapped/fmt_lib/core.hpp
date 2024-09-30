#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

// Define FSM_USE_ORIGINAL_FMTLIB_PLEASE    to use the original fmt library instead of the standard library.
// Define FSM_NO_FMT_HEADER_ONLY_PLEASE     to avoid getting the header only version of the fmt lib.
// Define FSM_FMTLIB_LOCALE_STUFF_PLEASE    to get the <locale> header and overloads using std locales.

#include <string>

#include <fsm/core/platform/cpp_version_macros.hpp>
#ifndef FSM_NO_FMT_HEADER_ONLY_PLEASE
#   if FSM_CPP_VERSION < FSM_CPP20
#       undef   FMT_HEADER_ONLY
#       define  FMT_HEADER_ONLY
#   endif
#endif

#ifdef FMT_HEADER_ONLY
#   undef   FSM_USE_ORIGINAL_FMTLIB_PLEASE
#   define  FSM_USE_ORIGINAL_FMTLIB_PLEASE
#endif

#if FSM_CPP_VERSION >= FSM_CPP20 and not defined( FSM_USE_ORIGINAL_FMTLIB_PLEASE )
#   undef   FSM_USING_ORIGINAL_FMTLIB       // = Using the standard library's adoption.
#else
#   undef   FSM_USING_ORIGINAL_FMTLIB
#   define  FSM_USING_ORIGINAL_FMTLIB
#endif

#ifdef FSM_FMTLIB_LOCALE_STUFF_PLEASE
#   include <locale>
#endif

#ifdef FSM_USING_ORIGINAL_FMTLIB
// #   pragma message "original fmt
#   include <fsm/core/wrapped/fmt_lib/_details/core.via-original-fmt-library.hpp>
#   include <fsm/core/wrapped/fmt_lib/_details/fmt_lib_version.hpp>
#else
// #   pragma message "fmt from standard library"
#   include <fsm/core/wrapped/fmt_lib/_details/core.via-stdlib.hpp>
#endif

namespace fsm_definitions {
    using   std::string;        // <string>

    // EXPORTS from the included headers (exposition + existence check only):
    namespace x = fmt_lib;  namespace fmt_lib_exports { using
        x::vformat, x::vformat_to,
        x::make_format_args, x::make_wformat_args,
        x::visit_format_arg,
        x::formatter,
        x::basic_format_arg,
        x::basic_format_args, x::format_args, x::wformat_args,
        x::basic_format_context, x::format_context, x::wformat_context,
        x::basic_format_parse_context, x::format_parse_context, x::wformat_parse_context,
        //
        x::api_provides_the_format_string_type,
        //
        x::format, x::format_to, // x::format_to_n, x::formatted_size,
        x::basic_format_string, x::format_string, x::wformat_string;
    }  // namespace fmt_lib_exports

    namespace fmt_lib {
        #if defined( FSM_USING_ORIGINAL_FMTLIB )
            const inline string fmt_lib_source = fmt_lib_description;     // E.g. "{{fmt}} version 9.11".
        #elif defined( FSM_BACKEND_PROVIDES_THE_FORMAT_STRING_TYPE )
            const inline string fmt_lib_source = "the C++ standard library";
        #else
            const inline string fmt_lib_source = "the C++ standard library + DIY supplements";
        #endif
    }
}  // namespace fsm_definitions
    
namespace fsm {
    inline namespace fmt_lib{ using namespace fsm_definitions::fmt_lib; }
}  // namespace fsm
