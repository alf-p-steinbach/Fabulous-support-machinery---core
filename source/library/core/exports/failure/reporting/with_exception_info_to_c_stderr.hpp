#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/declarations/type_builders.hpp>               // in_
#include <fsm/core/exports/failure/reporting/Failure_reporter_using_c_stderr.hpp>   // Failure_reporter
#include <fsm/core/exports/failure/reporting/with_exception_info_to.hpp>            // with_exception_info_to

#include <exception>
#include <functional>
#include <string_view>

#include <stdio.h>      // fprintf, fflush, stdout, stderr
#include <stdlib.h>     // EXIT_...

namespace fabulous_support_machinery::_definitions {

    inline auto with_exception_info_to_c_stderr( in_<Basic_main_func> main_func )
        -> int
    { return with_exception_info_to( Failure_reporter_using_c_stderr(), main_func ); }

    namespace d = _definitions;
    namespace exports { using
        d::with_exception_info_to_c_stderr;
    }  // namespace exports
}  // namespace fabuluous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace _definitions::exports; }
