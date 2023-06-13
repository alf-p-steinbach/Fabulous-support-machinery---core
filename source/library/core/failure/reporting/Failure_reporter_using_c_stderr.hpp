#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/constructs/declarations/type_builders.hpp>               // in_
#include <fsm/core/failure/reporting/Abstract_failure_reporter.hpp>         // Abstract_failure_reporter
#include <fsm/core/misc/support-for-collections/size-functions.hpp>         // int_size_of

#include <stdio.h>      // fprintf, fflush, stdout, stderr
#include <stdlib.h>     // EXIT_...

namespace fsm_definitions {
    namespace fsm = fabulous_support_machinery;
    using   fsm::in_,
            fsm::Abstract_failure_reporter,
            fsm::int_size_of;
    using   std::exception,         // <exception>
            std::string_view;       // <stringview>

    struct Failure_reporter_using_c_stderr:
        Abstract_failure_reporter
    {
        void output( in_<string_view> text ) const override
        {
            // TODO: only add newline to stdout if both stdout and stderr go to terminal.
            // TODO: attempt to set terminal temporarily to UTF-8.
            fprintf( stdout, "\n" );
            fflush( stdout );
            fprintf( stderr, "%.*s\n", int_size_of( text ), text.data() );
            fflush( stderr );
        }
    };

    namespace d = fsm_definitions;
    namespace exports { using
        d::Failure_reporter_using_c_stderr;
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace fsm_definitions::exports; }
