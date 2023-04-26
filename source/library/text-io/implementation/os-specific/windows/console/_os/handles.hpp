#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <fsm/core/exports/constructs/declarations/type_builders.hpp>       // const_
#include <fsm/core/exports/failure.hpp>                                     // hopefully, FSM_FAIL

#include <fsm/@wrapped/os/winapi/exports/windows-h.for-u16.hpp>

namespace fabulous_support_machinery::_os {

    // TODO: add proper closing of the handles.

    inline auto get_console_handle( const_<const wchar_t*> stream_name, const DWORD access )
        -> HANDLE
    {
        const HANDLE result = ::CreateFileW(
            stream_name,
            access,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            {},             // SECURITY_ATTRIBUTES
            OPEN_EXISTING,
            {},             // flags & attributes
            {}              // template file handle
            );
        hopefully( result != INVALID_HANDLE_VALUE )
            or FSM_FAIL( "Failed to obtain a console handle via CreateFileW." );
        return result;
    }

    inline auto console_input_handle()
        -> HANDLE
    {
        static const HANDLE result = get_console_handle( L"CONIN$", GENERIC_READ );
        return result;
    }

    inline auto console_output_handle()
        -> HANDLE
    {
        static const HANDLE result = get_console_handle( L"CONOUT$", GENERIC_WRITE );
        return result;
    }
}  // namespace fabulous_support_machinery::_os
