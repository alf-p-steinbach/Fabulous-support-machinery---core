#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/declarations/type_builders.hpp>       // in_
#include <fsm/core/exports/failure/x-classes/End_of_file.hpp>               // End_of_file
#include <fsm/core/exports/text/string_building.hpp>                        // string_from
#include <fsm/text-io/exports/Stream_id.hpp>                                // Output_stream_id

#include <string>
#include <string_view>
#include <utility>

namespace fabulous_support_machinery::std_streams::_definitions {
    using   std::string,                // <string>
            std::string_view,           // <string_view>
            std::move, std::forward;    // <utility>

    namespace os {
        extern auto input_using_buffer( string&& ) -> string;
        extern void output_to( Output_stream_id, in_<string_view> );
        extern void flush( Output_stream_id );
    }  // namespace os
    
    using os::input_using_buffer;
    using os::output_to;
    using os::flush;

    inline auto input() -> string                   { return input_using_buffer( "" ); }
    inline void output( in_<string_view> s )        { output_to( Stream_id::out, s ); }
    inline void output_err( in_<string_view> s )    { output_to( Stream_id::err, s ); }

    template< class... Args, FSM_ENABLE_IF( sizeof...( Args ) >= 2 ) >
    void output( Args&&... args )
    {
        output( string_from( forward<Args>( args )... ) );
    }

    template< class... Args, FSM_ENABLE_IF( sizeof...( Args ) >= 2 )  >
    void output_err( Args&&... args )
    {
        output_err( string_from( forward<Args>( args )... ) );
    }

    namespace d = _definitions;
    namespace exports{ using
        d::input_using_buffer,
        d::output_to,
        d::input,
        d::output,
        d::output_err;
    }  // namespace exports
}  // namespace fabulous_support_machinery::std_streams::_definitions

namespace fabulous_support_machinery::std_streams { using namespace _definitions::exports; }
