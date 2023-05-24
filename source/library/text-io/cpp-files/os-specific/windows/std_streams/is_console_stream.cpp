#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/headers/+std-cpp-language.hpp>

#include <fsm/text-io/headers/std_streams/is_console_stream.hpp>
#include <fsm/text-io/cpp-files/os-specific/windows/_os/stream_handle.hpp>

#include <fsm/@wrapped/os/winapi/exports/windows-h.for-u16.hpp>

namespace fabulous_support_machinery::std_streams::_definitions {
    
    auto is_console_stream( const Stream_id stream_id )
        -> bool
    {
        // TODO: cache.
        DWORD dummy;
        return ::GetConsoleMode( _os::stream_handle::for_id( stream_id ), &dummy );
    }
    
}  // namespace fabulous_support_machinery::std_streams::_definitions
