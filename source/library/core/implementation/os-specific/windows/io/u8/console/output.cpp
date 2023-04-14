// Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/io/u8/console/output.hpp>

#include <fsm/core/implementation/os-specific/windows/io/u8/stream_handle.hpp>
#include <fsm/core/implementation/os-specific/windows/_winapi/windows-h.for-u16.hpp>

#include <fsm/core/exports/basic-types/byte-types/Byte.hpp>
#include <fsm/core/exports/support-for-collections/size-functions.hpp>
#include <fsm/core/exports/constructs/failure-handling.hpp>     // hopefully, FSM_FAIL
#include <fsm/core/exports/text/encoding-conversions.hpp>
#include <fsm/core/exports/constructs/type_builders.hpp>

#include <array>        // std::array
#include <functional>   // std::invoke
#include <string>       // std::wstring
#include <string_view>  // std::wstring_view

#include <assert.h>     // assert
#include <stdlib.h>     // ::system

namespace fsm       = fabulous_support_machinery;

namespace impl {
    using fsm::hopefully;
    
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
}  // namespace impl

namespace fabulous_support_machinery::console {
    using   fsm::const_, fsm::in_;
    using   std::array,
            std::invoke,
            std::wstring,
            std::wstring_view;

    extern void _definitions::clear_screen()
    {
        system( "cls" );
    }

    // TODO: colorization depending on stream id
    extern void _definitions::output_to( const Output_stream_id stream_id, in_<string_view> s )
    {
        (void) stream_id;
        #ifndef __GNUC__
            struct stream_id;
        #endif
        if( s.empty() ) { return; }

        constexpr auto largest_dword = DWORD( -1 );

        const auto ws = text::to_utf_16_as_<wstring>( s );
        const Size ws_len = size_of( ws );
        assert( ws_len <= largest_dword );
        DWORD n_units_written = 0;
        const bool success = ::WriteConsole(
            impl::console_output_handle(),
            ws.data(),
            static_cast<DWORD>( ws_len ),
            &n_units_written,
            {}      // reserved
            );
        hopefully( success )
            or FSM_FAIL( "Failed to output to the console." );
    }
}  // namespace fabulous_support_machinery::console
