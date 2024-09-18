#pragma once    // Source encoding: UTF-8 (π is a lowercase Greek "pi").
//
// Functions and macro constants for signal management.

#ifndef REALLY_WANT_SIGNAL
#   error "`signal` doesn't work well with C++. You can define REALLY_WANT_SIGNAL."
#   include <stop-compilation>
#endif

#include <csignal>
#include <signal.h>
