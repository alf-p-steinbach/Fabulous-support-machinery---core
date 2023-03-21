#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/type_builders.hpp>        // in_

namespace fabulous_support_machinery {

    class Movable
    {
        using Self = Movable;
        Movable( in_<Self> ) = delete;
        auto operator=( in_<Self> ) -> Self& = delete;
        
    public:
        Movable() {}
        Movable( Self&& ) {}
        auto operator=( Self&& ) -> Self& { return *this; }
    };

}  // namespace fabulous_support_machinery
