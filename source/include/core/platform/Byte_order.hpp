#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

namespace fsm {
    
    // C++20 provides `std::endian`, <url: https://en.cppreference.com/w/cpp/types/endian>.
    // The definition below is a slightly modified copy of the possibility at cppreference.
    struct Byte_order{ enum Enum: int {
        #ifdef _WIN32       // 32- or 64-bit Windows.
            little_endian   = 0,
            big_endian      = 1,
            native          = little_endian
        #else   
            little_endian   = __ORDER_LITTLE_ENDIAN__,
            big_endian      = __ORDER_BIG_ENDIAN__,
            native          = __BYTE_ORDER__
        #endif
    }; };

}  // namespace fsm
