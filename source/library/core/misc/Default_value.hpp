#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

namespace fabulous_support_machinery {
    
    struct Default_value
    {
        template< class Type >
        operator Type () const { return {}; }
    };
}  // namespace fabulous_support_machinery
