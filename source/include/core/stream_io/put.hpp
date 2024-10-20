﻿#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/class_kinds/No_copy_or_move.hpp>             // No_copy_or_move
#include <fsm/core/exception_handling/FSM_FAIL.hpp>             // $fail
#include <fsm/core/platform/inspection/os_id_macros.hpp>        // FSM_OS_...
#include <fsm/core/parameter_passing/in_.hpp>                   // in_
#include <fsm/core/wrapped/fmt_lib/core.hpp>                    // -- {fmt} lib stuff.

#include <cstdio>
#include <stdio.h>          // fileno
#include <string_view>
#include <utility>

#if defined( FSM_OS_IS_WINDOWS )
#   include <io.h>
#elif defined( FSM_OS_IS_UNIX )
#   include <unistd.h>      // isatty
#else
#   error "This platform is not supported."
#   include <stop-compilation>
#endif

namespace fsm_definitions {
    using   fsm::No_copy_or_move, fsm::in_,
            fsm::now, fsm::fail,
            fsm::in_,
            fsm::format_string, fsm::vformat, fsm::make_format_args;
    using   std::fwrite,            // <cstdio>
            std::string_view,       // <string_view>
            std::forward;           // <utility>

    #ifdef FSM_OS_IS_WINDOWS
        inline const auto fileno = _fileno;         // <stdio.h>
        inline const auto isatty = _isatty;         // <io.h>

        // TODO:
        struct Console_encoding_fix: No_copy_or_move
        {
            ~Console_encoding_fix() {}
            Console_encoding_fix() {}
        };
    #else
        struct Console_encoding_fix: No_copy_or_move
        {
            ~Console_encoding_fix() {}
            Console_encoding_fix() {}
        };
    #endif

    namespace stream_io {
        using Stream_handle = FILE*;

        inline auto is_console( const Stream_handle stream )
            -> bool
        { return isatty( fileno( stream ) ); }

        inline void put_to( const Stream_handle stream, in_<string_view> s )
        {
            static const Console_encoding_fix   a_fix;  // In Windows sets active codepage 65001 (UTF-8).

            const auto n_bytes_written = fwrite( s.data(), 1, s.size(), stream );
            now( n_bytes_written == s.size() )
                or $fail( "fwrite failed" );
        }

        inline void put( in_<string_view> s ) { put_to( stdout, s ); }

        inline void put_line_to( const Stream_handle stream, in_<string_view> s )
        {
            put_to( stream, s );
            put_to( stream, "\n" );
        }

        inline void put_line( in_<string_view> s ) { put_line_to( stdout, s ); }


        //--------------------------------------------------------------- With formatting:

        template< class... Args >
        inline void put_to( const Stream_handle stream, format_string<Args...> fmt, Args&&... args )
        {
            put_to( stream, format( fmt, forward<Args>( args )... ) );
        }

        template< class... Args >
        inline void put( format_string<Args...> fmt, Args&&... args )
        {
            put_to( stdout, format( fmt, forward<Args>( args )... ) );
        }

        template< class... Args >
        inline void put_line_to( const Stream_handle stream, format_string<Args...> fmt, Args&&... args )
        {
            put_to( stream, format( fmt, forward<Args>( args )... ) );
            put_to( stream, "\n" );
        }

        template< class... Args >
        inline void put_line( format_string<Args...> fmt, Args&&... args )
        {
            put_to( stdout, format( fmt, forward<Args>( args )... ) );
            put_to( stdout, "\n" );
        }
    }  // namespace stream_io
}  // namespace fsm_definitions

namespace fsm {
    inline namespace stream_io { using namespace fsm_definitions::stream_io; }
}  // namespace fsm
