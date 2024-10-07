#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <fsm/core/class_kinds/No_copy_or_move.hpp>     // No_copy_or_move
#include <fsm/core/exception_handling/now_and_fail.hpp> // TODO: FSM_FAIL
#include <fsm/core/platform/os_id_macros.hpp>           // FSM_OS_...
#include <fsm/core/parameter_passing/in_.hpp>           // in_
#include <fsm/core/wrapped/fmt_lib/core.hpp>            // -- {fmt} lib stuff.

#include <cstdio>
#include <stdio.h>          // fileno
#include <string>
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
            fsm::format_string, fsm::vformat, fsm::make_format_args;
    using   std::fwrite,            // <cstdio>
            std::string,            // <string>
            std::string_view,       // <string_view>
            std::forward;           // <utility>

    #ifdef FSM_OS_IS_WINDOWS
        inline const auto fileno = _fileno;         // <stdio.h>
        inline const auto isatty = _isatty;         // <io.h>
        
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

        inline void put( const Stream_handle stream, in_<string_view> s )
        {
            static const Console_encoding_fix   a_fix;  // In Windows sets active codepage 65001 (UTF-8).

            const auto n_bytes_written = fwrite( s.data(), 1, s.size(), stream );
            now( n_bytes_written == s.size() )
                or fail( "fwrite failed" );             // TODO: use FSM_FAIL
        }

        inline void put( in_<string> s ) { put( stdout, s.c_str() ); }

        inline void put_line( const Stream_handle stream, in_<string> s )
        {
            put( stream, s.c_str() );
            put( stream, "\n" );
        }

        inline void put_line( in_<string> s ) { put_line( stdout, s ); }


        //--------------------------------------------------------------- With formatting:
        
        template< class... Args >
        inline void put( const Stream_handle stream, format_string<Args...> fmt, Args&&... args )
        {
            put( stream, format( fmt, forward<Args>( args )... ) );
        }
        
        template< class... Args >
        inline void put( format_string<Args...> fmt, Args&&... args )
        {
            put( stdout, format( fmt, forward<Args>( args )... ) );
        }
 
        template< class... Args >
        inline void put_line( const Stream_handle stream, format_string<Args...> fmt, Args&&... args )
        {
            put( stream, format( fmt, forward<Args>( args )... ) );
            put( stream, "\n" );
        }

        template< class... Args >
        inline void put_line( format_string<Args...> fmt, Args&&... args )
        {
            put( stdout, format( fmt, forward<Args>( args )... ) );
            put( stdout, "\n" );
        }

    }  // namespace stream_io
}  // namespace fsm_definitions

namespace fsm {
    inline namespace stream_io {
        using namespace fsm_definitions::stream_io;
    }
}  // namespace fsm
