#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/text-io/std_streams/failure-reporting/with_xinfo_to_err_stream.hpp>

namespace fabulous_support_machinery {
    
    inline auto with_exceptions_displayed( void run() )
        -> int
    { return std_streams::with_xinfo_to_err_stream( run ); }
    
}  // namespace fabulous_support_machinery
