#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

// <url: https://en.cppreference.com/w/cpp/preprocessor/replace#Predefined_macros>
#define FSM_CPP_VERSION     __cplusplus

#define FSM_CPP98           199711L
#define FSM_CPP03           FSM_CPP98
#define FSM_CPP11           201103L
#define FSM_CPP14           201402L
#define FSM_CPP17           201703L
#define FSM_CPP20           202002L

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
