#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

// Mainly boolean `and`, `or` and `not`.
//
// And mainly just a Visual C++ (MSVC) conformance issue.
//
// Up until some unknown version MSVC did not provide `and`, `or` and `not` natively
// and instead defined them, + the other alternate keywords, as macros in `<iso646.h>`.
#ifdef _MSC_VER
#   // Safe because MSVC versions that support the alternate keywords natively, define
#   // the macros conditionally: `#if !defined(__cplusplus) || defined(_MSC_EXTENSIONS)`
#   include <iso646.h>                  // Standard `and` etc. also with older MSVC.
#endif
