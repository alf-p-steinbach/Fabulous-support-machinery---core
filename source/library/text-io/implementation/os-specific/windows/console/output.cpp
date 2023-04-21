// Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/text-io/exports/console/output.hpp>

#include <fsm/text-io/implementation/os-specific/windows/_stream_handle.hpp>

#include <fsm/core/exports/basic-types/byte-types/Byte.hpp>
#include <fsm/core/exports/failure.hpp>                                     // hopefully, FSM_FAIL
#include <fsm/core/exports/support-for-collections/size-functions.hpp>
#include <fsm/core/exports/text/encoding-conversions.hpp>
#include <fsm/core/exports/constructs/declarations/FSM_WITHOUT_USING.hpp>   // FSM_WITHOUT_USING
#include <fsm/core/exports/constructs/declarations/type_builders.hpp>

#include <fsm/@wrapped/os/winapi/exports/windows-h.for-u16.hpp>

#include <array>        // std::array
#include <functional>   // std::invoke
#include <string>       // std::wstring
#include <string_view>  // std::wstring_view

#include <assert.h>     // assert
#include <stdlib.h>     // ::system

namespace fsm       = fabulous_support_machinery;

namespace fabulous_support_machinery::impl {
    
    static auto get_console_input_handle()
        -> HANDLE
    {
        const HANDLE result = CreateFileW(
            L"CONIN$",
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ,
            nullptr,        // SECURITY_ATTRIBUTES
            OPEN_EXISTING,
            {},             // flags & attributes
            {}              // template file handle
            );
        hopefully( result != INVALID_HANDLE_VALUE )
            or FSM_FAIL( "Failed to obtain a console input handle via CreateFileW." );
        return result;
    }

    static auto console_input_handle()
        -> HANDLE
    {
        static const HANDLE result = get_console_input_handle();
        return result;
    }

    static auto get_console_output_handle()
        -> HANDLE
    {
        const HANDLE result = CreateFileW(
            L"CONOUT$",
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_WRITE,
            nullptr,        // SECURITY_ATTRIBUTES
            OPEN_EXISTING,
            {},             // flags & attributes
            {}              // template file handle
            );
        hopefully( result != INVALID_HANDLE_VALUE )
            or FSM_FAIL( "Failed to obtain a console output handle via CreateFileW." );
        return result;
    }

    static auto console_output_handle()
        -> HANDLE
    {
        static const HANDLE result = get_console_output_handle();
        return result;
    }
}  // namespace fabulous_support_machinery::impl

namespace fabulous_support_machinery::console {
    using   fsm::const_, fsm::in_;
    using   std::array,
            std::invoke,
            std::wstring,
            std::wstring_view;

    void _definitions::clear_screen()
    {
        system( "cls" );        // TODO: find out how to do this reliably via API.
    }

    // TODO: colorization depending on stream id
    void _definitions::output_to( const Output_stream_id stream_id, in_<string_view> s )
    {
        FSM_WITHOUT_USING( stream_id ) {
            if( s.empty() ) { return; }

            constexpr auto max_dword = DWORD( -1 );

            const auto ws = text::to_utf_16_as_<wstring>( s );
            const Size ws_len = size_of( ws );
            assert( ws_len <= max_dword );
            DWORD n_units_written = 0;
            const bool success = ::WriteConsole(
                impl::console_output_handle(),
                ws.data(),
                static_cast<DWORD>( ws_len ),
                &n_units_written,
                {}      // reserved
                );
            hopefully( success )
                or FSM_FAIL( "Failed to output to the console via WriteConsole." );
        }
    }
}  // namespace fabulous_support_machinery::console
