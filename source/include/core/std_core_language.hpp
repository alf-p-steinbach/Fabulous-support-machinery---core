#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

//------------------------------------------------------------------------- Enabling:
#include <fsm/core/std_core_language/enable-std-literals.hpp>           // Syntax.
#include <fsm/core/std_core_language/enable-alternate-keywords.hpp>     // Syntax.
#include <fsm/core/std_core_language/core-language-headers.hpp>         // Semantics.

//------------------------------------------------------------------------- Requirements:
// TODO: assert minimum language version
#include <fsm/core/assertions/literals_are_utf8.hpp>                    // Encoding.
