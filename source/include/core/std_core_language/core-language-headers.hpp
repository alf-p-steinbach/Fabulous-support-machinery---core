#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <fsm/core/platform/cpp_version_macros.hpp>     // FSM_CPP_VERSION etc.

#include <fsm/core/c/assert.hpp>    // assert
#include <fsm/core/c/stddef.hpp>    // size_t and ptrdiff_t.
#include <fsm/core/c/stdlib.hpp>    // EXIT_FAILURE, EXIT_SUCCESS.
        
#include <initializer_list>         // std::initializer_list, for use in range based `for`.
#include <new>                      // std::operator new, for placement `new` expressions.
#include <typeinfo>                 // std::type_info, for using `typeid`.

#if FSM_CPP_VERSION >= FSM_CPP20
#   include <compare>               // For checking result of spaceship operator `<=>`.
#endif
