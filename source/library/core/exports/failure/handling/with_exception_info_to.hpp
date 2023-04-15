#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/type_builders.hpp>             // in_
#include <fsm/core/exports/failure/handling/Failure_reporter.hpp>    // Failure_reporter

#include <exception>
#include <functional>
#include <string_view>

#include <stdio.h>      // fprintf, fflush, stdout, stderr
#include <stdlib.h>     // EXIT_...

namespace fabulous_support_machinery::_definitions {
    using   std::exception,         // <exception>
            std::function,          // <functional>
            std::string_view;       // <stringview>

    using Basic_main_func           = function<void()>;

    inline auto with_exception_info_to(
        in_<Failure_reporter>       reporter,
        in_<Basic_main_func>        main_func
        )
        -> int
    {
        try {
            main_func();
            return EXIT_SUCCESS;
        // TODO: clean application exit exception.
        // TODO: use terminal aware output.
        // TODO: nested exceptions' messages.
        } catch( in_<exception> x ) {
            reporter.report( x );
        } catch( ... ) {
            reporter.report_unexpected();
        }
        return EXIT_FAILURE;
    }

    namespace d = _definitions;
    namespace exports { using
        d::Basic_main_func,
        d::with_exception_info_to;
    }  // namespace exports
}  // namespace fabluous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace _definitions::exports; }
