#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <fsm/core/exception_handling/now-and-fail.hpp>
#include <fsm/core/introspection/FSM_FUNCNAME.hpp>
#include <fsm/core/wrapped/fmt_lib/core.hpp>

#define FSM_FAIL( msg ) \
    fsm::fail( fsm::format( "{} - {}", FSM_FUNCNAME, msg ) )

#ifndef FSM_NO_DOLLAR_MACROS_PLEASE
#   define $fail    FSM_FAIL
#endif
