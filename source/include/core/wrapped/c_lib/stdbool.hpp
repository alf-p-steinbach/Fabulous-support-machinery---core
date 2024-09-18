#pragma once    // Source encoding: UTF-8 (π is a lowercase Greek "pi").
//
// Defines the `__bool_true_false_are_defined` compatibility macro constant.
// In C it also defines `bool` as a macro that expands to `_Bool`, and
// `true` and `false` as integer constants 1 and 0, respectively.
// C++ has a built-in `bool` type so this header is ~never needed in C++.

#include <cstdbool>
#include <stdbool.h>
