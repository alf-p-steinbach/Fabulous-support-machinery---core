#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/exception/throwing/now-and-fail.hpp>             // fsm::fail_
#include <fsm/core/constructs/introspection/FSM_FUNCNAME.hpp>       // FSM_FUNCNAME
#include <fsm/core/wrapped/fmt_lib/core.hpp>                        // fsm::format

#include <string>

#if 0
    // Untested C++20 code:
    #define FSM_FAIL_( X, msg_literal, ... ) \
        fsm::fail_<X>( fsm::format( ("{} - " msg_literal), FSM_FUNCNAME __VA_OPT__(,) __VA_ARGS__ ) )

    #define FSM_FAIL( msg_literal, ... ) \
        FSM_FAIL_( std::runtime_error, msg_literal __VA_OPT__(,) __VA_ARGS__ )
#endif

// Works with C++17 but not so clear code and a little needless inefficiency:  // TODO: improve
#define FSM_FAIL_( X, ... ) \
    fsm::fail_<X>( std::string( FSM_FUNCNAME ) + " - " + fsm::format( __VA_ARGS__ ) )

#define FSM_FAIL( ... ) \
    FSM_FAIL_( std::runtime_error, __VA_ARGS__ )

#define $fail_  FSM_FAIL_
#define $fail   FSM_FAIL
