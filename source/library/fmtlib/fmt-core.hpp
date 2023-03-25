#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

// Define FSM_USE_ORIGINAL_FMTLIB_PLEASE to use the original fmt library instead of the standard library.
// Define FSM_NO_FMT_HEADER_ONLY_PLEASE to avoid getting the header only version of the fmt lib.
// Define FSM_FMTLIB_LOCALE_STUFF_PLEASE to get the <locale> header and overloads using std locales.

#include <fsm/core/exports/+std-cpp-language/versions.hpp>
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
#   define  FSM_USING_ORIGINAL_FMTLIB
#endif

#if __cplusplus >= (2020*100 + 2)
#   include <concepts>
#endif
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

#include <stddef.h>         // size_t
#include <cstddef>          // std::size_t

#ifdef FSM_FMTLIB_LOCALE_STUFF_PLEASE
#   include <locale>
#endif

#ifdef FSM_USING_ORIGINAL_FMTLIB
    #include <fmt/core.h>
    #include <fmt/xchar.h>      // wchar_t support
#else
    #include <format>
#endif

// Common (reliable) namespace pollution.
namespace fabulous_support_machinery::fmtlib {
    using   std::string, std::wstring,      // <string>
            std::basic_string_view,         // <string_view>
            std::forward;                   // <utility>

    #if __cplusplus >= (2020*100 + 2)
        using   std::convertible_to,            // <concepts> C++20
                std::iter_difference_t,         // <iterator> C++20
                std::type/identity_t;           // <type_traits> C++20
    #endif

    #ifdef FSM_FMTLIB_LOCALE_STUFF_PLEASE
        using   std::locale;                    // <locale>
    #endif
}  // namespace fabulous_support_machinery::fmtlib

#ifdef FSM_USING_ORIGINAL_FMTLIB
    namespace fabulous_support_machinery::fmtlib {
        using namespace fmt;

        #define FSM_FMTLIB_API_PROVIDES_FORMAT_STRING_TYPE
        constexpr bool api_provides_format_string_type = true;
    }  // namespace fabulous_support_machinery::fmtlib
#else
    namespace fabulous_support_machinery::fmtlib {
        using   //std::format, std::format_to, std::format_to_n, std::formatted_size,
                std::vformat, std::vformat_to,
                std::make_format_args, std::make_wformat_args,
                std::visit_format_arg,
                std::formatter,
                std::basic_format_arg,
                std::basic_format_args, std::format_args, std::wformat_args,
                //std::basic_format_string, ...  -- See #if below
                std::basic_format_context, std::format_context, std::wformat_context,
                std::basic_format_parse_context, std::format_parse_context, std::wformat_parse_context;
                
        #if __cpp_lib_format >= (2022*100 + 7)
            #define FSM_FMTLIB_API_PROVIDES_FORMAT_STRING_TYPE
            constexpr bool api_provides_format_string_type = true;

            using   std::format, std::format_to, std::format_to_n, std::formatted_size,
                    std::basic_format_string, std::format_string, std::wformat_string;
        #else
            // <url: https://en.cppreference.com/w/cpp/utility/format#Notes>
            // std::basic_format_string is not exposed.
            #undef FSM_FMTLIB_API_PROVIDES_FORMAT_STRING_TYPE
            constexpr bool api_provides_format_string_type = false;
            
            template< class Char_, class... Args_ >
            class basic_format_string
            {
                using Sv = basic_string_view<Char_>;
                Sv m_sv;

            public:
                // The templating avoids a double user-defined conversion which would exclude
                // this constructor from overload resolution.
                template< class T >
                    requires convertible_to<const T&, Sv>
                constexpr basic_format_string( const T& fmt_spec ):
                    m_sv( fmt_spec )
                {} // TODO: Compile time parse
                
                constexpr auto get() const -> Sv { return m_sv; }
                //constexpr operator string_view() const { return m_sv; }   -- ?
            };

            template< class... Args_ >
            using format_string = basic_format_string< char, type/identity_t<Args_>...>;

            template< class... Args_ >
            using wformat_string = basic_format_string< wchar_t, type/identity_t<Args_>...>;
            
            template< class... Args >
            inline auto format( format_string<Args...> fmt, Args&&... args )
                -> string
            { return vformat( fmt.get(), make_format_args( forward<Args>( args )... ) ); }

            // To avoid `std::format` with internal arg type being considered by overload resolution.
            template< class... Args >
            inline auto format( const_<const char*> fmt, Args&&... args )
                -> string
            { return vformat( fmt, make_format_args( forward<Args>( args )... ) ); }

            template< class... Args >
            inline auto format( wformat_string<Args...> fmt, Args&&... args )
                -> wstring
            { return vformat( fmt.get(), make_wformat_args( forward<Args>( args )... ) ); }

            // To avoid `std::format` with internal arg type being considered by overload resolution.
            template< class... Args >
            inline auto format( const_<const wchar_t*> fmt, Args&&... args )
                -> string
            { return vformat( fmt, make_format_args( forward<Args>( args )... ) ); }

            #ifdef FSM_FMTLIB_LOCALE_STUFF_PLEASE
                template< class... Args >
                inline auto format( const locale& loc, format_string<Args...> fmt, Args&&... args )
                    -> string
                { return vformat( loc, fmt.get(), make_format_args( forward<Args>( args )... ) ); }

                template< class... Args >
                inline auto format( const locale& loc, wformat_string<Args...> fmt, Args&&... args )
                    -> string
                { return vformat( loc, fmt.get(), make_wformat_args( forward<Args>( args )... ) ); }
            #endif  // FSM_FMTLIB_LOCALE_STUFF_PLEASE

            template< class OutputIt, class... Args >
            inline auto format_to( OutputIt out, format_string<Args...> fmt, Args&&... args )
                -> OutputIt
            { return std::vformat_to( out, fmt.get(), make_format_args( forward<Args>( args)... ) ); }

            template< class OutputIt, class... Args >
            inline auto format_to( OutputIt out, wformat_string<Args...> fmt, Args&&... args )
                -> OutputIt
            { return vformat_to( out, fmt.get(), make_wformat_args( forward<Args>( args )... ) ); }

            #ifdef FSM_FMTLIB_LOCALE_STUFF_PLEASE
                template< class OutputIt, class... Args >
                inline auto format_to(
                    OutputIt out, const locale& loc, format_string<Args...> fmt, Args&&... args
                    )
                    -> OutputIt
                { return vformat_to( out, loc, fmt.get(), make_format_args( forward<Args>( args )... ) ); }
                
                template< class OutputIt, class... Args >
                inline auto format_to(
                    OutputIt out, const locale& loc, wformat_string<Args...> fmt, Args&&... args
                    )
                    -> OutputIt
                { return vformat_to( out, loc, fmt.get(), make_wformat_args( forward<Args>( args )... ) ); }
            #endif  // FSM_FMTLIB_LOCALE_STUFF_PLEASE

            // `format_to_n` is not provided, because
            //
            // - unclear whether `n` refers to encoding units or code points, and
            // - unclear how to implement relatively efficiently.
            
            #if 0
                // TODO: Needs definition of `Counting_iterator`
                // TODO: signed return type?
                template< class... Args >
                inline auto formatted_size( format_string<Args...> fmt, Args&&... args )
                    -> size_t
                {
                    const Counting_iterator it_start{};
                    const Counting_iterator it_end = format_to( it_start, fmt, forward<Args>( args )... );
                    return it_end - it_start;
                }
            #endif
         #endif  // [else of] __cpp_lib_format >= (2022*100 + 7)
    }  // namespace fabulous_support_machinery::fmtlib
#endif  // [else of] FSM_USING_ORIGINAL_FMTLIB
