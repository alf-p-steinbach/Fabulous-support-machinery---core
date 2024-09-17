#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

// When _USE_MATH_DEFINES is defined a Posix-compliant `<math.h>` defines M_PI etc.
// <url: https://www.gnu.org/software/libc/manual/html_node/Mathematical-Constants.html>
// Note: g++ may also require that `__STRICT_ANSI__` is not defined.
//
// C++20 and later offer corresponding names as typed constants via `<numbers>`.
// <url: https://en.cppreference.com/w/cpp/numeric/constants>
//
// I.e. this assert is only reasonable for C or for code intended as C++17 or earlier.

#ifndef _USE_MATH_DEFINES
#   error "This program needs macro _USE_MATH_DEFINES defined in the build command."
#   include <stop-compilation>
#endif

#include <fsm/core/c/math.hpp>
#ifndef M_PI
#   error "M_PI not defined by <math.h> (apparently included without _USE_MATH_DEFINES)."
#   include <stop-compilation>
#endif
