#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

// Example usage:
//
//      template< class Item, FSM_ENABLE_IF( sizeof( Item ) == 1 ) >
//      auto to_char_ptr( Item* ) -> char*;
//
// Or with $-macros from header <fsm/$-macros.hpp>:
//
//      template< class Item, $enable_if( sizeof( Item ) == 1 ) >
//      auto to_char_ptr( Item* ) -> char*;


#include <fsm/core/exports/constructs/declarations/enable_if_.hpp>

#define FSM_ENABLE_IF( ... ) \
    std::enable_if_t<__VA_ARGS__>* = nullptr
