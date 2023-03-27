#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/type_builders.hpp>        // in_
#include <fsm/core/exports/io/u8/console.hpp>        // console::*
#include <fsm/fmtlib/fmt-core.hpp>           // fmtlib::*

#include <iterator>
#include <string>
#include <utility>

namespace fabulous_support_machinery::console::_definitions {
    using   std::back_inserter,         // <iterator>
            std::string,                // <string>
            std::forward;               // <utility>

    template<class... Args>
    using format_string = fmtlib::basic_format_string<char, Args...>;
    
    using F = fmtlib::format_string<int>;
    
    // Operations for `string` buffer. For other buffer types e.g. define these to be found via ADL.
    inline void clear( string& s ) { s.clear(); }
    inline auto string_view_of( in_<string> s ) -> auto { return string_view( s ); }

    template< class Buffer, class... Args >
    void print_fmt_using_buffer(
        Buffer&&                                buffer,
        const Output_stream_id                  stream_id,
        in_<fmtlib::format_string< Args...>>    fmt,
        Args&&...                               args
        )
    {
        clear( buffer );
        fmtlib::format_to( back_inserter( buffer ), fmt, forward<Args>( args )... );
        output_to( stream_id, string_view_of( buffer ) );
    }

    template< class... Args >
    void print_fmt_to(
        const Output_stream_id                  stream_id,
        in_<fmtlib::format_string< Args...>>    fmt,
        Args&&...                               args
        )
    {
        print_fmt_using_buffer( string(), stream_id, fmt, forward< Args >( args )... );
    }
    
    template< class... Args >
    void print_fmt( in_<fmtlib::format_string< Args...>> fmt, Args&&... args )
    {
        print_fmt_to( Stream_id::out, fmt, forward< Args >( args )... );
    }

    template< class... Args >
    void print_fmt_err( in_<fmtlib::format_string< Args...>> fmt, Args&&... args )
    {
        output_to( Stream_id::err, fmt, forward< Args >( args )... );
    }

    namespace useful_ns_names {
        // Already defined by console header:
        //      namespace console   = fsm::console;
        //      namespace u8        = fsm::u8;
        //      namespace unicode   = fsm::unicode;
        namespace fmtlib    = fsm::fmtlib;
    }  // namespace useful_ns_names

    namespace d = _definitions;
    namespace exports{ using
        d::print_fmt_using_buffer,
        d::print_fmt_to,
        d::print_fmt,
        d::print_fmt_err;
        namespace useful_ns_names = d::useful_ns_names;
    }  // namespace exports
}  // namespace fabulous_support_machinery::console::_definitions

namespace fabulous_support_machinery::console   { using namespace _definitions::exports; }
