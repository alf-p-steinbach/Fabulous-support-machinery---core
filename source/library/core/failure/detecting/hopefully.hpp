#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

namespace fabulous_support_machinery {

    constexpr auto hopefully( const bool condition ) noexcept
        -> bool
    { return condition; }

}  // namespace fabulous_support_machinery
