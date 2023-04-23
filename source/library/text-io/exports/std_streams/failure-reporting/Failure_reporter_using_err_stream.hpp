#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/declarations/type_builders.hpp>       // in_
#include <fsm/core/exports/failure/reporting/Abstract_failure_reporter.hpp> // Abstract_failure_reporter
#include <fsm/core/exports/support-for-collections/size-functions.hpp>      // is_empty, int_size_of
#include <fsm/text-io/exports/std_streams/io.hpp>                           // output

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
            // TODO: only add newline to stdout if both stdout and stderr go to terminal.
            output_err( "\n", text );
            // TODO: flush();
        }
    };

    namespace d = _definitions;
    namespace exports { using
        d::Failure_reporter_using_err_stream;
    }  // namespace exports
}  // namespace fabulous_support_machinery::std_streams::_definitions

namespace fabulous_support_machinery::std_streams   { using namespace _definitions::exports; }
