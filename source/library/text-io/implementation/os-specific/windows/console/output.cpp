// Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/text-io/exports/console/output.hpp>

#include <fsm/text-io/implementation/os-specific/windows/console/_os/handles.hpp>

#include <fsm/core/exports/failure.hpp>                                     // hopefully, FSM_FAIL
#include <fsm/core/exports/support-for-collections/size-functions.hpp>      // size_of, is_empty
#include <fsm/core/exports/text/encoding-conversions.hpp>                   // to_utf_16_as_
#include <fsm/core/exports/constructs/declarations/FSM_NOT_USING.hpp>       // FSM_NOT_USING

#include <fsm/@wrapped/os/winapi/exports/windows-h.for-u16.hpp>             // WriteConsole

#include <string>       // std::wstring

#include <assert.h>     // assert
#include <stdlib.h>     // system

namespace fsm       = fabulous_support_machinery;

namespace fabulous_support_machinery::console::_definitions {
    using   std::wstring;           // <string>

    constexpr auto max_dword = DWORD( -1 );

    void os::clear_screen()
    {
        system( "cls" );        // TODO: find out how to do this reliably via API.
    }

    // TODO: colorization depending on stream id -- OK to do at exports level?
    void os::output_to( const Output_stream_id stream_id, in_<string_view> s )
    {
        FSM_NOT_USING( stream_id ) {
            if( is_empty( s ) ) { return; }
            const auto ws = text::to_utf_16_as_<wstring>( s );
            const Size ws_len = size_of( ws );
            assert( ws_len <= max_dword );

            DWORD n_units_written = 0;
            ::WriteConsole(
                _os::console_output_handle(),
                ws.data(),
                static_cast<DWORD>( ws_len ),
                &n_units_written,
                {}      // reserved
                ) or FSM_FAIL( "Failed to output to the console via WriteConsole." );
            assert( n_units_written == ws_len );
        }
    }
}  // namespace fabulous_support_machinery::console::_definitions
