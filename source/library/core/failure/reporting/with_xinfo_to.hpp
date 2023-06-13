#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/constructs/declarations/type_builders.hpp>             // in_
#include <fsm/core/failure/reporting/Abstract_failure_reporter.hpp>    // Abstract_failure_reporter

#include <exception>
#include <functional>
#include <string_view>

#include <stdio.h>      // fprintf, fflush, stdout, stderr
#include <stdlib.h>     // EXIT_...

namespace fsm_definitions {
    namespace fsm = fabulous_support_machinery;
    using   fsm::in_,
            fsm::Abstract_failure_reporter;
    using   std::exception,         // <exception>
            std::function,          // <functional>
            std::string_view;       // <stringview>

    using Basic_main_func           = function<void()>;

    inline auto with_xinfo_to(
        in_<Abstract_failure_reporter>      reporter,
        in_<Basic_main_func>                main_func
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

    template< class Failure_reporter >
    auto with_xinfo_to_( in_<Basic_main_func> main_func )
        -> int
    { return with_xinfo_to( Failure_reporter(), main_func ); }

    namespace d = fsm_definitions;
    namespace exports { using
        d::Basic_main_func,
        d::with_xinfo_to,
        d::with_xinfo_to_;
    }  // namespace exports
}  // namespace fabluous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace fsm_definitions::exports; }
