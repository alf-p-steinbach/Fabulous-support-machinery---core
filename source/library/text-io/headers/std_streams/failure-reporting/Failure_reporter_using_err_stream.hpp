#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/headers/+std-cpp-language.hpp>

#include <fsm/core/headers/constructs/declarations/type_builders.hpp>       // in_
#include <fsm/core/headers/failure/reporting/Abstract_failure_reporter.hpp> // Abstract_failure_reporter
#include <fsm/core/headers/misc/support-for-collections/size-functions.hpp>      // is_empty, int_size_of
#include <fsm/text-io/headers/std_streams/io.hpp>                           // output
#include <fsm/text-io/headers/std_streams/is_console_stream.hpp>            // is_console_stream

#include <stdio.h>      // fprintf, fflush, stdout, stderr
#include <stdlib.h>     // EXIT_...

namespace fabulous_support_machinery::std_streams::_definitions {
    using   std::exception,         // <exception>
            std::string_view;       // <stringview>

    struct Failure_reporter_using_err_stream:
        Abstract_failure_reporter
    {
        void output( in_<string_view> text ) const override
        {
            for( const auto id: { Stream_id::out, Stream_id::err } ) { flush( id ); }
            if( is_console_stream( Stream_id::out ) and is_console_stream( Stream_id::err ) ) {
                output_err( "\n" );
            }
            output_err( text, "\n" );
            flush( Stream_id::err );
        }
    };

    namespace d = _definitions;
    namespace exports { using
        d::Failure_reporter_using_err_stream;
    }  // namespace exports
}  // namespace fabulous_support_machinery::std_streams::_definitions

namespace fabulous_support_machinery::std_streams   { using namespace _definitions::exports; }
