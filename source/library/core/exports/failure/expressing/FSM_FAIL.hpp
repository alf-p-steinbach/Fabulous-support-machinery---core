#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

// Example usage:
//
//      delete_file( path ) or FSM_FAIL( "delete_file failed" );
//
// Or with $-macros from header <fsm/$-macros.hpp>:
//
//      delete_file( path ) or $fail( "delete_file failed" );

#include <fsm/core/exports/constructs/introspection/FSM_FUNCTION_NAME.hpp>
#include <fsm/core/exports/failure/expressing/fail.hpp>
#include <fsm/core/exports/failure/x-classes/default_message_for_.hpp>


#define FSM_FAILURE_MESSAGE( explanation ) \
    std::string() + FSM_FUNCTION_NAME + " - " + (explanation)

#define FSM_FAIL_WITH_ARGS_( X, args_list ) \
    ::fabulous_support_machinery::fail_<X> args_list

#define FSM_FAIL_WITH_DEFAULT_MESSAGE_( X ) \
    FSM_FAIL_WITH_ARGS_( X, ( ::fabulous_support_machinery::x::default_message_for_<X>() ) )

#define FSM_FAIL_( X, explanation ) \
    FSM_FAIL_WITH_ARGS_( X, ( FSM_FAILURE_MESSAGE( explanation ) ) )

#define FSM_FAIL( explanation ) \
    FSM_FAIL_( std::runtime_error, explanation )
