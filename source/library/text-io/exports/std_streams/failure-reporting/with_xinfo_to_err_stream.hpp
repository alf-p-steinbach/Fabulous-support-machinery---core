#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/failure/reporting/with_xinfo_to.hpp>
#include <fsm/text-io/exports/std_streams/failure-reporting/Failure_reporter_using_err_stream.hpp>

namespace fabulous_support_machinery::std_streams {

    constexpr inline auto& with_xinfo_to_err_stream = with_xinfo_to_<
        Failure_reporter_using_err_stream
    >;

}  // namespace fabluous_support_machinery::std_streams
