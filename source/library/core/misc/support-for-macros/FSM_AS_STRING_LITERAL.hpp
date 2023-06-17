#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#define FSMi_VALUE_AS_STRING_LITERAL( ... )     #__VA_ARGS__
#define FSM_AS_STRING_LITERAL( macro_name )     FSMi_VALUE_AS_STRING_LITERAL( macro_name )
