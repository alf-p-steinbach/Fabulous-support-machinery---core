#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

// Mainly boolean `and`, `or` and `not`.
// Mainly just a Visual C++ (MSVC) conformance issue.
//
// Up until some unknown version MSVC did not provide `and`, `or` and `not` natively
// and instead defined them, + the other alternate keywords, as macros in `<iso646.h>`.
//
// After some unknown version but <1941, MSVC stopped providing `<iso646.h>` even though
// it's still required in C++20 (however C++20 dropped the `<ciso646>` header).
//
#ifdef _MSC_VER
#   if _MSC_VER < 1900  // Hopefully neither too early nor too late version cutoff.
#       // Safe because MSVC versions that support the alternate keywords natively, define
#       // the macros conditionally: `#if !defined(__cplusplus) || defined(_MSC_EXTENSIONS)`
#       include <iso646.h>                  // Standard `and` etc. also with older MSVC.
#   endif
#endif
