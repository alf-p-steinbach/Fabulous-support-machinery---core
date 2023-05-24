﻿#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/headers/+std-cpp-language.hpp>

// Define FSM_USE_ORIGINAL_FMTLIB_PLEASE to use the original fmt library instead of the standard library.
// Define FSM_NO_FMT_HEADER_ONLY_PLEASE to avoid getting the header only version of the fmt lib.
// Define FSM_FMTLIB_LOCALE_STUFF_PLEASE to get the <locale> header and overloads using std locales.

#include <fsm/core/headers/+std-cpp-language/versions.hpp>
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

#if defined( __cpp_lib_format ) and not defined( FSM_USE_ORIGINAL_FMTLIB_PLEASE )
#   undef   FSM_USING_ORIGINAL_FMTLIB
#else
#   undef   FSM_USING_ORIGINAL_FMTLIB
#   define  FSM_USING_ORIGINAL_FMTLIB
#endif

#ifdef FSM_FMTLIB_LOCALE_STUFF_PLEASE
#   include <locale>
#endif

#ifdef FSM_USING_ORIGINAL_FMTLIB
#   include <fsm/@wrapped/3rd-party-lib/fmtlib/headers/_details/fmt-core.via-original-fmt-library.hpp>
#else
#   include <fsm/@wrapped/3rd-party-lib/fmtlib/headers/_details/fmt-core.via-stdlib.hpp>
#endif

namespace fsm_definitions::fmtlib {
    namespace x = fmtlib;
    namespace exports { using
        x::vformat, x::vformat_to,
        x::make_format_args, x::make_wformat_args,
        x::visit_format_arg,
        x::formatter,
        x::basic_format_arg,
        x::basic_format_args, x::format_args, x::wformat_args,
        x::basic_format_context, x::format_context, x::wformat_context,
        x::basic_format_parse_context, x::format_parse_context, x::wformat_parse_context,
        //
        x::api_provides_format_string_type,
        //
        x::format, x::format_to, x::format_to_n, x::formatted_size,
        x::basic_format_string, x::format_string, x::wformat_string;
    }  // namespace exports
}  // namespace fsm_definitions::fmtlib
    
namespace fabulous_support_machinery{
    // `fmtlib::` stuff is intentionally not available unqualified in fsm namespace.

    // Not a simple equate because may need to be an extension of earlier declared namespace.
    namespace fmtlib{
        using namespace fsm_definitions::fmtlib::exports;
    }  // namespace fmtlib
}  // namespace fabulous_support_machinery
