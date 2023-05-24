#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/headers/+std-cpp-language.hpp>

#include <fsm/core/headers/constructs/declarations/type_builders.hpp>      // in_

namespace fabulous_support_machinery {
    
    class Non_instantiable
    {
        using Self = Non_instantiable;
        Non_instantiable() = delete;
        Non_instantiable( in_<Self> ) = delete;
    };

}  // namespace fabulous_support_machinery
