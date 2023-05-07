#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/failure/detecting/FSM_STATIC_ASSERT.hpp>

#include <limits.h>     // CHAR_BIT

namespace fabulous_support_machinery {
    constexpr int bits_per_byte = CHAR_BIT;
    FSM_STATIC_ASSERT( bits_per_byte == 8 );    // Compilers with byte != octet are rare but do exist!

    constexpr int max_byte_value = static_cast<unsigned char>( -1 );    // 255 for an octet, all bits 1.
}  // namespace fabulous_support_machinery
