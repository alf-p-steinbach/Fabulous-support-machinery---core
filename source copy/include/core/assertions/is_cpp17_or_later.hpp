#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/inspection/cpp_version_macros.hpp>

#if FSM_CPP_VERSION < FSM_CPP17
#   error "Too old C++ (the FSM library needs C++17 or later)"   // E.g. `string_view`.
#   include <stop-compilation>
#endif
