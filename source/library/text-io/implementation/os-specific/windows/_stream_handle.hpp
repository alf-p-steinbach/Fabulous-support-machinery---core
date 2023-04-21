#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/text-io/exports/Stream_id.hpp>
#include <fsm/core/exports/constructs/declarations/type_builders.hpp>

#include <fsm/@wrapped/os/winapi/exports/windows-h.for-u16.hpp>

#include <io.h>     // Windows-specific _get_osfhandle.

#include    <array>     // std::array

namespace fsm = fabulous_support_machinery;
using   fsm::const_, fsm::in_;

namespace fabulous_support_machinery::impl {
    namespace stream_handle {
        using   std::array;

        // TODO: express as singletons via a templated meyers'.
        inline const_<HANDLE>  in   = GetStdHandle( STD_INPUT_HANDLE );
        inline const_<HANDLE>  out  = GetStdHandle( STD_OUTPUT_HANDLE );
        inline const_<HANDLE>  err  = GetStdHandle( STD_ERROR_HANDLE );

        inline auto for_id( const Stream_id id )
            -> HANDLE
        {
            if( +id <= 2 ) {
                static const auto std_handles = array{ in, out, err };
                return std_handles[+id];
            } else {
                return reinterpret_cast<HANDLE>( _get_osfhandle( +id ) );
            }
        }
    }  // namespace stream_handle
}  // namespace fabulous_support_machinery::impl
