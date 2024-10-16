#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/constructs/introspection/FSM_FUNCNAME/FSM_RAW_FUNC_DECL.hpp>         // FSM_RAW_FUNC_DECL
#include <fsm/core/constructs/introspection/FSM_FUNCNAME/funcname_from_raw_decl.hpp>    // funcname_from_raw_decl

#define FSM_FUNCNAME    fsm_definitions::funcname_from_raw_decl( FSM_RAW_FUNC_DECL )
#define $funcname       FSM_FUNCNAME
