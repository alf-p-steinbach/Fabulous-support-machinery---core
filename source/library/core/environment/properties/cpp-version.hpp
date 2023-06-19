#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <fsm/core/environment/properties/FSM_CPPdd.hpp>            // FSM_CPP..

namespace fabulous_support_machinery {
    enum: long {
        cpp_version     = FSM_CPP_VERSION,

        cpp98           = FSM_CPP98,
        cpp03           = FSM_CPP03,
        cpp11           = FSM_CPP11,
        cpp14           = FSM_CPP14,
        cpp17           = FSM_CPP17,
        cpp20           = FSM_CPP20
    };
}  // namespace fabulous_support_machinery
