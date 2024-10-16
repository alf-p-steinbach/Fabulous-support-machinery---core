#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <fsm/core/platform/inspection/cpp_version_macros.hpp>
#include <fsm/core/type_builders.hpp>           // const_, in_

#include <format>           // Requires C++20 or later.  Defines `__cpp_lib_format`.
#include <concepts>         // Requires C++20 or later.

#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

#include <stddef.h>         // size_t
#include <cstddef>          // std::size_t

#undef FSM_BACKEND_PROVIDES_THE_FORMAT_STRING_TYPE      // May be defined below.

namespace fsm_definitions {
    using   fsm::in_, fsm::const_;
    using   std::convertible_to,            // <concepts> C++20
            std::iter_difference_t,         // <iterator> C++20
            std::string, std::wstring,      // <string>
            std::basic_string_view,         // <string_view>
            std::forward,                   // <utility>
            std::type_identity_t;           // <type_traits> C++20

    #ifdef FSM_FMTLIB_LOCALE_STUFF_PLEASE
        using   std::locale;                    // <locale>
    #endif

    namespace fmt_lib {
        using   //std::format, std::format_to, std::format_to_n, std::formatted_size,   -- see below #if.
                std::vformat, std::vformat_to,
                std::make_format_args, std::make_wformat_args,
                std::visit_format_arg,
                std::formatter,
                std::basic_format_arg,
                std::basic_format_args, std::format_args, std::wformat_args,
                //std::basic_format_string, ...  -- See #if below
                std::basic_format_context, std::format_context, std::wformat_context,
                std::basic_format_parse_context, std::format_parse_context, std::wformat_parse_context;
                
        // <url: https://en.cppreference.com/w/cpp/utility/format#Notes>
        // `std::basic_format_string` is not exposed prior to C++ <format> header version 202207.
        //
        // But (reason for `FSM_PLEASE_FIX_FORMAT` option macro):
        //
        // “We intentionally treat the addition of std::basic_format_string (P2508) as a defect report
        // because all known implementations make these components available in C++20 mode, although it
        // is not so categorized officially.”
        //
        #if __cpp_lib_format >= (2022*100 + 7) or not defined( FSM_PLEASE_FIX_FORMAT )
            #define FSM_BACKEND_PROVIDES_THE_FORMAT_STRING_TYPE

            constexpr bool api_provides_the_format_string_type = true;

            using   std::format, std::format_to, std::format_to_n, std::formatted_size,
                    std::basic_format_string, std::format_string, std::wformat_string;
        #else
            constexpr bool api_provides_the_format_string_type = false;
            
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
            using format_string = basic_format_string< char, type_identity_t<Args_>...>;

            template< class... Args_ >
            using wformat_string = basic_format_string< wchar_t, type_identity_t<Args_>...>;
            
            template< class... Args >
            inline auto format( format_string<Args...> fmt, Args&&... args )
                -> string
            { return vformat( fmt.get(), make_format_args( forward<const Args>( args )... ) ); }

            // To avoid `std::format` with internal arg type being considered by overload resolution.
            template< class... Args >
            inline auto format( const_<const char*> fmt, Args&&... args )
                -> string
            { return vformat( fmt, make_format_args( forward<const Args>( args )... ) ); }

            template< class... Args >
            inline auto format( wformat_string<Args...> fmt, Args&&... args )
                -> wstring
            { return vformat( fmt.get(), make_wformat_args( forward<const Args>( args )... ) ); }

            // To avoid `std::format` with internal arg type being considered by overload resolution.
            template< class... Args >
            inline auto format( const_<const wchar_t*> fmt, Args&&... args )
                -> string
            { return vformat( fmt, make_format_args( forward<const Args>( args )... ) ); }

            #ifdef FSM_FMTLIB_LOCALE_STUFF_PLEASE
                template< class... Args >
                inline auto format( const locale& loc, format_string<Args...> fmt, Args&&... args )
                    -> string
                { return vformat( loc, fmt.get(), make_format_args( forward<const Args>( args )... ) ); }

                template< class... Args >
                inline auto format( const locale& loc, wformat_string<Args...> fmt, Args&&... args )
                    -> string
                { return vformat( loc, fmt.get(), make_wformat_args( forward<const Args>( args )... ) ); }
            #endif  // FSM_FMTLIB_LOCALE_STUFF_PLEASE

            template< class OutputIt, class... Args >
            inline auto format_to( OutputIt out, format_string<Args...> fmt, Args&&... args )
                -> OutputIt
            { return std::vformat_to( out, fmt.get(), make_format_args( forward<const Args>( args)... ) ); }

            template< class OutputIt, class... Args >
            inline auto format_to( OutputIt out, wformat_string<Args...> fmt, Args&&... args )
                -> OutputIt
            { return vformat_to( out, fmt.get(), make_wformat_args( forward<const Args>( args )... ) ); }

            #ifdef FSM_FMTLIB_LOCALE_STUFF_PLEASE
                template< class OutputIt, class... Args >
                inline auto format_to(
                    OutputIt out, const locale& loc, format_string<Args...> fmt, Args&&... args
                    )
                    -> OutputIt
                { return vformat_to( out, loc, fmt.get(), make_format_args( forward<const Args>( args )... ) ); }
                
                template< class OutputIt, class... Args >
                inline auto format_to(
                    OutputIt out, const locale& loc, wformat_string<Args...> fmt, Args&&... args
                    )
                    -> OutputIt
                { return vformat_to( out, loc, fmt.get(), make_wformat_args( forward<const Args>( args )... ) ); }
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
    }  // namespace fmt_lib
}  // namespace fsm_definitions
