#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/exception_handling/now-and-fail.hpp>
#include <fsm/core/constructs/introspection/FSM_FUNCNAME.hpp>
#include <fsm/core/wrapped/fmt_lib/core.hpp>

#define FSM_FAIL_( X, msg ) \
    fsm::fail_<X>( fsm::format( "{} - {}", FSM_FUNCNAME, msg ) )

#define FSM_FAIL( msg ) \
    FSM_FAIL_( std::runtime_error, msg )

#define $fail_  FSM_FAIL_
#define $fail   FSM_FAIL
