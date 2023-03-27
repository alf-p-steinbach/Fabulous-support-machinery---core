﻿#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

// Intentionally doesn't include everything in that directory. Some of it is just
// there as nice-to-have functionality. For when some library user needs it.

//------------------------------------------------------------------------- Enabling:
#include <fsm/core/exports/+std-cpp-language/enable-std-literals.hpp>            // Syntax.
#include <fsm/core/exports/+std-cpp-language/full-core-language-headers.hpp>     // Semantics.
    
//------------------------------------------------------------------------- Requirements:
#include <fsm/core/exports/+std-cpp-language/asserted.is_cpp17_or_better.hpp>    // C++ version.
#include <fsm/core/exports/+std-cpp-language/asserted.utf8-literals.hpp>         // Encoding.
