#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/failure/detecting/FSM_STATIC_ASSERT.hpp>     // FSM_STATIC_ASSERT

#include <limits.h>     // CHAR_BIT

namespace fabulous_support_machinery {

    using Byte  = unsigned char;

    constexpr int bits_per_byte = CHAR_BIT;
    FSM_STATIC_ASSERT( bits_per_byte == 8 );    // Compilers with byte != octet not supported.

    constexpr int max_byte_value = static_cast<unsigned char>( -1 );    // 255, all bits 1.
    
    template< class Type >
    constexpr bool is_byte_ = (sizeof( Type ) == 1);

}  // namespace fabulous_support_machinery
