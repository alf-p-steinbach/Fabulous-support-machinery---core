#pragma once    // Source encoding: UTF-8 (π is a lowercase Greek "pi").
//
// C-style Unicode character conversion functions, e.g. `mblen`, `mbtowc`.
// + allegedly `char16_t` and `char32_t`.

#include <cuchar>

// TODO: conditionally include <uchar.h> and provide workaround for Apple.
// #include <uchar.h>
