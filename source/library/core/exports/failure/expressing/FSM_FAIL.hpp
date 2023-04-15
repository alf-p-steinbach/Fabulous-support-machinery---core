#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

// Example usage:
//
//      delete_file( path ) or FSM_FAIL( "delete_file failed" );
//
// Or with $-macros from header <fsm/$-macros.hpp>:
//
//      delete_file( path ) or $fail( "delete_file failed" );


#include <fsm/core/exports/failure/expressing/fail.hpp>

// TODO: pick up namespace/class via __FUNCTION__ or the like.
#define FSM_FUNCTION_NAME   __func__

#define FSM_FAILURE_MESSAGE( explanation ) \
    std::string() + FSM_FUNCTION_NAME + " - " + (explanation)

#define FSM_FAIL_( X, explanation ) \
    ::fabulous_support_machinery::fail_<X>( FSM_FAILURE_MESSAGE( explanation ) )

#define FSM_FAIL( explanation ) \
    ::fabulous_support_machinery::fail( FSM_FAILURE_MESSAGE( explanation ) )
