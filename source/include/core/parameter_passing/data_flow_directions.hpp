﻿#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

namespace fsm_definitions {
    namespace parameter_passing {

        template< class T > using in_       = const T&;
        template< class T > using in_out_   = T&;

    }  // namespace parameter_passing
}  // namespace fsm_definitions

namespace fsm {
    inline namespace parameter_passing { using namespace fsm_definitions::parameter_passing; }
}  // namespace fsm
