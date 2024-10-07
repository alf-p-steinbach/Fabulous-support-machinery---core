#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#undef      FSM_OS_IS_WINDOWS
#undef          FSM_OS_IS_WIN32
#undef          FSM_OS_IS_WIN64
#undef      FSM_OS_IS_UNIX
#undef          FSM_OS_IS_LINUX
#undef          FSM_OS_IS_IOS
#undef              FSM_OS_IS_IOS_IN_SIMULATOR
#undef              FSM_OS_IS_IOS_ON_DEVICE
#undef          FSM_OS_IS_MAC_OS

#if defined( _WIN64 )
#   define FSM_OS_IS_WIN64                          1
#   define FSM_OS_IS_WINDOWS                        1
#elif defined( _WIN32 )     // Note: _WIN32 is defined also for 64-bit Windows; FSM_OS_IS_WIN32 isn't.
#   define FSM_OS_IS_WIN32                          1
#   define FSM_OS_IS_WINDOWS                        1
#else
#   if defined( unix ) || defined( __unix__ ) || defined( __unix )
#       define FSM_OS_IS_UNIX                       1
#       if defined( __linux__ )
#           define FSM_OS_IS_LINUX                  1
#       endif
#   endif
#   if defined( __APPLE__ ) && defined( __MACH__ )
#       undef  FSM_OS_IS_UNIX
#       define FSM_OS_IS_UNIX                       1
#       include <TargetConditionals.h>      // An Appple header.
#       if TARGET_IPHONE_SIMULATOR == 1
#           define  FSM_OS_IS_IOS_IN_SIMULATOR      1
#           define  FSM_OS_IS_IOS                   1
#       elif TARGET_OS_IPHONE == 1
#           define  FSM_OS_IS_IOS_ON_IDEVICE        1    // iOS on iPhone, iPad, etc.
#           define  FSM_OS_IS_IOS                   1
#       elif TARGET_OS_MAC == 1
#           define  FSM_OS_IS_MAC_OS                1
#       endif
#   endif
#endif

#ifdef FSM_OS_IS_UNIX
#   undef   __unix__
#   define  __unix__
#endif

namespace fsm {
    constexpr bool os_is_windows =
    #ifdef FSM_OS_IS_WINDOWS
        true;
    #else
        false;
    #endif
}  // namespace fsm
