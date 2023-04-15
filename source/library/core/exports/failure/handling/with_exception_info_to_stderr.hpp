#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/type_builders.hpp>                         // in_
#include <fsm/core/exports/failure/handling/Failure_reporter_using_stderr.hpp>   // Failure_reporter
#include <fsm/core/exports/failure/handling/with_exception_info_to.hpp>          // with_exception_info_to

#include <exception>
#include <functional>
#include <string_view>

#include <stdio.h>      // fprintf, fflush, stdout, stderr
#include <stdlib.h>     // EXIT_...

namespace fabulous_support_machinery::_definitions {

    inline auto with_exception_info_to_stderr( in_<Basic_main_func> main_func )
        -> int
    { return with_exception_info_to( Failure_reporter_using_stderr(), main_func ); }

    namespace d = _definitions;
    namespace exports { using
        d::with_exception_info_to_stderr;
    }  // namespace exports
}  // namespace fabluous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace _definitions::exports; }
