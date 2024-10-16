#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

//------------------------------------------------------------------------- Requirements:

#include <fsm/core/assertions/is_cpp17_or_later.hpp>                                // Language features.
#include <fsm/core/assertions/literals_are_utf8.hpp>                                // Encoding.
#include <fsm/core/assertions/int_is_more_than_16_bits.hpp>                         // `int` number range.

//------------------------------------------------------------------------- Enabling:
#include <fsm/core/platform/std_core_language/enable-std-literals.hpp>              // Syntax.
#include <fsm/core/platform/std_core_language/enable-alternate-keywords.hpp>        // Syntax.
#include <fsm/core/platform/std_core_language/enable-core-language-semantics.hpp>   // Semantics.

//------------------------------------------------------------------------- Disabling:
#ifdef __clang__
#   pragma clang diagnostic ignored "-Wunqualified-std-cast-call"                   // Sabotaging warning.
#endif
