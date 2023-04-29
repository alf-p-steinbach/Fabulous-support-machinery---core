#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/failure/reporting/with_xinfo_to.hpp>
#include <fsm/core/exports/failure/reporting/Failure_reporter_using_c_stderr.hpp>

namespace fabulous_support_machinery {

    constexpr inline auto& with_xinfo_to_c_stderr = with_xinfo_to_<
        Failure_reporter_using_c_stderr
    >;

}  // namespace fabulous_support_machinery

