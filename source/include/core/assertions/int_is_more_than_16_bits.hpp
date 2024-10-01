#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

// The preprocessor is unusable for this because MinGW g++ and MSVC are non-conforming.
// This means that compilation can't be stopped.
// At least not without some compiler-specific measures.
#if (-1u == 0xFFFF'FFFF'FFFF'FFFF )
//#   error gah, 64-bits!      // If uncommented this always kicks in with MinGW g++ and MSVC. :(
#endif

static_assert( unsigned( -1 ) > 0xFFFF, "The `int` type is only 16 bits (too small number range)." );
