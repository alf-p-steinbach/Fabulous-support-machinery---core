// Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/text-io/console/input.hpp>

#include <fsm/core/constructs/declarations/type_builders.hpp>       // const_
#include <fsm/core/failure/detecting/hopefully.hpp>                 // hopefully
#include <fsm/core/failure/expressing/FSM_FAIL.hpp>                 // FSM_FAIL*

#include <string>
#include <utility>

#include <assert.h>     // assert
#include <stdio.h>      // fgetc

namespace fabulous_support_machinery::console::_definitions {
    using   std::string,        // <string>
            std::move;          // <utility>

    // TODO: replace with use of Windows console functions for UTF-8 single-line input.
    static auto console_input_using_buffer( string&& buffer )
        -> string
    {
        static const_<FILE*> console = ::fopen( "con:", "r" );

        assert( console != nullptr );
        buffer.clear();
        for( ;; ) {
            const int code = ::fgetc( console );
            if( code == EOF ) {
                // The `getchar` return value EOF also covers the case of error.
                hopefully( not ferror( stdin ) )    // With MSVC 2022 `feof` is always false here.
                    or FSM_FAIL( "The standard input stream failed (C ferror is true)" );
                // True logical EOF established. Then:
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
    
    auto os::input_using_buffer( string&& buffer )
        -> string
    { return console_input_using_buffer( move( buffer ) ); }

}  // namespace fabulous_support_machinery::console::_definitions

