#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/text-io/exports/std_streams/io.hpp>       // ~

#include <fsm/core/exports/constructs/declarations/type_builders.hpp>                    // const_, in_
#include <fsm/core/exports/failure/detecting/hopefully.hpp>                 // hopefully
#include <fsm/core/exports/failure/expressing/FSM_FAIL.hpp>                 // FSM_FAIL
#include <fsm/core/exports/support-for-collections/size-functions.hpp>      // int_size_of, is_empty
#include <fsm/text-io/exports/console/input.hpp>                            // console::input
#include <fsm/text-io/exports/std_streams/is_console_stream.hpp>            // is_console_stream

#include <utility>
#include <stdio.h>      // fprintf

namespace fabulous_support_machinery::std_streams::_definitions {
    using   std::move;          // <utility>

    auto input_using_buffer( string&& buffer )
        -> string
    {
        // if( is_console_stream( Stream_id::in ) ) {
            // // TODO: return console::input_using_buffer( move( buffer ) );
            // return "";
        // } else {
            buffer.clear();
            for( ;; ) {
                const int code = getchar();
                if( code == EOF ) {
                    // Note: `getchar` return value EOF also covers the case of error.
                    hopefully( feof( stdin ) )
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
        // }
    }
    
    void output_to( const Output_stream_id stream_id, in_<string_view> s )
    {
        if( is_console_stream( stream_id ) ) {
            console::output_to( stream_id, s );
        } else {
            const_<FILE*> f = (stream_id == Stream_id::out? stdout : stderr);
            fprintf( f, "%.*s", int_size_of( s ), s.data() );
        }
    }
    
}  // namespace fabulous_support_machinery::std_streams::_definitions
