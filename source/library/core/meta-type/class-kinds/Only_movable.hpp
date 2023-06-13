#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/constructs/declarations/type_builders.hpp>        // in_

namespace fabulous_support_machinery {

    class Only_movable
    {
        using Self = Only_movable;
        Only_movable( in_<Self> ) = delete;
        auto operator=( in_<Self> ) -> Self& = delete;
        
    public:
        Only_movable() {}
        Only_movable( Self&& ) {}
        auto operator=( Self&& ) -> Self& { return *this; }
    };

}  // namespace fabulous_support_machinery
