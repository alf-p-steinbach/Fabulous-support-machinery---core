#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <fsm/core/constructs/FSM_FUNC_ID/FSM_RAW_FUNC_DECL.hpp>      // FSM_RAW_FUNC_DECL
#include <fsm/core/constructs/FSM_FUNC_ID/func_id_from_raw_decl.hpp>  // func_id_from_raw_decl

#define FSM_FUNC_ID   fsm_definitions::func_id_from_raw_decl( FSM_RAW_FUNC_DECL )
