#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

// A comment macro for e.g. prefix and inline comments:
#define FSM_FUNCNAME    __func__            // TODO: properly qualified name

#ifndef FSM_NO_DOLLAR_MACROS_PLEASE
#   define $funcname    FSM_FUNCNAME
#endif
