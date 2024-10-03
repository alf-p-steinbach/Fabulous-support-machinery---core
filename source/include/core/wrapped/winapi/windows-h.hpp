#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>
//
// In this file custom macros (not Microsoft's macros) have names with "WINAPI" in them:
// 
//   WINAPI_IS_CHAR_BASED, WINAPI_VERSION, WINAPI_SERVICE_PACK
//
// Ideal usage:
// define `WINAPI_VERSION` in the build settings, or anyway before including this file.
// `WINAPI_VERSION` has the same values as Microsoft's `_WIN32_WINNT` and `WINVER`.

#ifdef MessageBox
#   error "<windows.h> has already been included, possibly with undesired options."
#   include <stop-compilation>      // For e.g. the g++ compiler.
#endif

#include <assert.h>

#if defined( WINAPI_IS_CHAR_BASED ) and defined( UNICODE )
#   error "Inconsistent, both UNICODE (UTF-16) and WINAPI_IS_CHAR_BASED (ANSI/UTF-8) are defined."
#   include <stop-compilation>      // For e.g. the g++ compiler.
#endif

#if defined( _MBCS ) and defined( UNICODE )
#   error "Inconsistent, both UNICODE (UTF-16) and _MBCS (Windows multibyte) are defined."
#   include <stop-compilation>      // For e.g. the g++ compiler.
#endif

#if not( defined( WINAPI_IS_CHAR_BASED ) or defined( UNICODE ) )
#   error "Define either WINAPI_IS_CHAR_BASED or UNICODE for respectively ANSI/UTF-8 and UTF-16."
#   include <stop-compilation>      // For e.g. the g++ compiler.
#endif

#undef UNICODE
#undef _UNICODE
#ifdef WINAPI_IS_CHAR_BASED
#   undef _MBCS
#   define _MBCS        // Mainly for 3rd party code that uses it for platform detection.
#else
#   define UNICODE
#   define _UNICODE     // Mainly for 3rd party code that uses it for platform detection.
#endif
#undef STRICT           // C++-compatible “strongly typed” declarations, please.
#define STRICT
#undef NOMINMAX         // No C++-sabotaging “min” and “max” macros, please.
#define NOMINMAX

// Reduce the size of the <windows.h>, to the degree practically possible.
// Also, with WIN32_LEAN_AND_MEAN an `#include <winsock2.h>` will actually include that header.
#undef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#undef NOCOMM           // No serial comms API please.
#define NOCOMM
#undef NOMCX            // No modem configuration API please.
#define NOMCX
#undef NOOPENFILE       // No OpenFile function please; it's limited and long deprecated.
#define NOOPENFILE

// With much stuff introduced in Windows Vista and later one needs to set version indicators.
// NTDDI_VERSION (newest macro), _WIN32_WINNT and WINVER (oldest macro) are used by <windows.h>.
// WINAPI_VERSION and WINAPI_SERVICE_PACK are macros used by and optionally defined by this header.
//
// Experience shows that one needs to take full control of this, especially with g++, so:
//
#if defined( WINAPI_VERSION )
#   undef   NTDDI_VERSION
#   undef   _WIN32_WINNT
#   undef   WINVER
#else
#   undef WINAPI_SERVICE_PACK
#   if defined( NTDDI_VERSION )
#       undef   _WIN32_WINNT
#       undef   WINVER
#       define  WINAPI_VERSION          (NTDDI_VERSION >> 16)
#       define  WINAPI_SERVICE_PACK     (NTTDI_VERSION & 0xFFFF)
#   elif defined( _WIN32_WINNT )
#       undef   WINVER
#       define  WINAPI_VERSION          _WIN32_WINNT
#   elif defined( WINVER )
#       define  WINAPI_VERSION          WINVER
#   else
#       define  WINAPI_VERSION          0x0600      // Default, Windows Vista.
#   endif
#endif

#ifndef WINAPI_SERVICE_PACK
#   define  WINAPI_SERVICE_PACK         0
#endif

#ifndef NTDDI_VERSION
#   define NTDDI_VERSION    ((WINAPI_VERSION << 16) | WINAPI_SERVICE_PACK)
#endif

#ifndef _WIN32_WINNT
#   define _WIN32_WINNT     WINAPI_VERSION
#endif

#ifndef WINVER
#   define WINVER           WINAPI_VERSION
#endif


/////////////////////////////////////////////////////////////////////
#include <windows.h>                                                //
/////////////////////////////////////////////////////////////////////

// Use like `static_assert( IS_NARROW_WINAPI() )`.
#define IS_NARROW_WINAPI()      (sizeof(*GetCommandLine()) == 1)
#define IS_WIDE_WINAPI()        (sizeof(*GetCommandLine()) > 1)
