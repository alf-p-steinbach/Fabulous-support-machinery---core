#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

// A comment macro for e.g. prefix and inline comments:
#define FSM_( ... )     // Intentionally expands to nothing.

#ifndef FSM_NO_DOLLAR_MACROS_PLEASE
#   define $_ FSM_
#endif
