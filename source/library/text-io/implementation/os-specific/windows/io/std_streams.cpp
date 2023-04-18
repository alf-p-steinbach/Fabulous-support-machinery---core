// Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/text-io/exports/std_streams.hpp>

#include <fsm/text-io/implementation/os-specific/windows/io/stream_handle.hpp>

#include <fsm/core/exports/basic-types/byte-types/Byte.hpp>
#include <fsm/core/exports/failure.hpp>
#include <fsm/core/exports/support-for-collections/size-functions.hpp>
#include <fsm/core/exports/text/encoding-conversions.hpp>
#include <fsm/core/exports/constructs/type_builders.hpp>

#include <fsm/@wrapped/os/winapi/exports/windows-h.for-u16.hpp>

#include <array>        // std::array

#include <assert.h>

namespace fsm       = fabulous_support_machinery;
using   fsm::const_, fsm::in_;

namespace fabulous_support_machinery::u8 {
    using   std::wstring,
            std::wstring_view;

    auto u8_length_of( const wstring_view& )
        -> Size
    { return 0; }       // TODO

    auto _definitions::Std_streams_core::input_using_buffer( string&& buffer )
        -> string
    {
        (void) buffer;
        return "";
    }

    void _definitions::Std_streams_core::output_to( const Stream_id stream_id, in_<string_view> s )
    {
        if( s.empty() ) { return; }
        assert( stream_id != Stream_id::in );

        constexpr auto largest_dword = DWORD( -1 );

        const auto ws = text::to_utf_16_as_<wstring>( s );
        const Size ws_len = size_of( ws );
        assert( ws_len <= largest_dword );
        DWORD n_units_written = 0;
        const bool success = ::WriteConsole(
            stream_handle::for_id( stream_id ),
            ws.data(),
            static_cast<DWORD>( ws_len ),
            &n_units_written,
            {}      // reserved
            );
        hopefully( success )
            or FSM_FAIL( "Failed to output to the standard output stream." );
    }
}  // namespace fabulous_support_machinery::u8
