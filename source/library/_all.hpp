#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core.hpp>
#include <fsm/text-io.hpp>

#ifndef FSM_NO_FMT_LIB_PLEASE
#   include <fsm/@wrapped/3rd-party-lib/fmtlib.hpp>
#endif

#if 0  // Copy+paste template:
    #if __has_include( <fsm/FOO.hpp> )
    #   include <fsm/FOO.hpp>
    #endif
#endif

#if __has_include( <fsm/stdlib-alts.hpp> )
#   include <fsm/stdlib-alts.hpp>
#endif
