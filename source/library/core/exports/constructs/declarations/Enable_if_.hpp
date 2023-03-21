#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <utility>

namespace fabulous_support_machinery {
    
    template< bool condition >
    using Enable_if_ = std::enable_if_t<condition, bool>;
    
}  // namespace fabulous_support_machinery
