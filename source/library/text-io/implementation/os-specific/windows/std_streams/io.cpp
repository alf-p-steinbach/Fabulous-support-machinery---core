#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/text-io/exports/std_streams/io.hpp>       // ~

#include <fsm/core/exports/constructs/declarations/type_builders.hpp>       // const_, in_
#include <fsm/core/exports/failure/detecting/hopefully.hpp>                 // hopefully
#include <fsm/core/exports/failure/expressing/FSM_FAIL.hpp>                 // FSM_FAIL
#include <fsm/core/exports/support-for-collections/size-functions.hpp>      // int_size_of, is_empty
#include <fsm/text-io/exports/console/input.hpp>                            // console::input
#include <fsm/text-io/exports/std_streams/is_console_stream.hpp>            // is_console_stream

#include <utility>

#include <assert.h>     // assert
#include <stdio.h>      // fprintf

namespace fabulous_support_machinery::std_streams::_definitions {
    using   std::move;          // <utility>

    static auto stdin_input_using_buffer( string&& buffer )
        -> string
    {
        buffer.clear();
        for( ;; ) {
            const int code = ::getchar();
            if( code == EOF ) {
                // Note: `getchar` return value EOF also covers the case of error.
                hopefully( ::feof( stdin ) )
                    or FSM_FAIL( "The standard input stream failed (C ferror is true)" );
                hopefully( not is_empty( buffer ) )
                    or FSM_FAIL_WITH_DEFAULT_MESSAGE_( x::End_of_file );
                break;
            } else if( code == '\n' ) {
                break;
            }
            buffer += char( code );
        }
        return move( buffer );
    }

    static auto c_file_from( const Output_stream_id stream_id )
        -> FILE*
    {
        switch( stream_id ) {
            case Stream_id::out:    return stdout;
            case Stream_id::err:    return stderr;
            default:
                assert( !"Unknown output stream id." );
        }
        for( ;; ) {}    // Should never get here.
    }

    auto os::input_using_buffer( string&& buffer )
        -> string
    {
        if( is_console_stream( Stream_id::in ) ) {
            return console::input_using_buffer( move( buffer ) );
        } else {
            return stdin_input_using_buffer( move( buffer ) );
        }
    }

    void os::output_to( const Output_stream_id stream_id, in_<string_view> s )
    {
        if( is_console_stream( stream_id ) ) {
            console::output_to( stream_id, s );
        } else {
            ::fprintf( c_file_from( stream_id ), "%.*s", int_size_of( s ), s.data() );
        }
    }
    
    void os::flush( const Output_stream_id stream_id )
    {
        ::fflush( c_file_from( stream_id ) );
    }

}  // namespace fabulous_support_machinery::std_streams::_definitions
