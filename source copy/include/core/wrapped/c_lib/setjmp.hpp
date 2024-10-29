#pragma once    // Source encoding: UTF-8 (π is a lowercase Greek "pi").
//
// Macro (and function) that saves (and jumps) to an execution context.

#ifndef REALLY_WANT_SETJMP
#   error "`setjmp` doesn't work well with C++. You can define REALLY_WANT_SETJMP to get it."
#   include <stop-compilation>
#endif

#include <csetjmp>
#include <setjmp.h>
