#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

// Relevant e.g. to avoid unnecessary copying for use of `std::filesystem::path::u8string()`.
// Also, is basis for definition of `Byte_order`.
#ifdef _WIN32
#   define  FSM_OS_IS_WINDOWS   true
#else
#   define  FSM_OS_IS_WINDOWS   false
#endif

namespace fabulous_support_machinery {
    constexpr bool os_is_windows = FSM_OS_IS_WINDOWS;
}  // namespace fabulous_support_machinery
