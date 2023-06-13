#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/constructs/declarations/FSM_ENABLE_IF.hpp>       // FSM_ENABLE_IF
#include <fsm/core/constructs/declarations/type_builders.hpp>       // in_
#include <fsm/core/text/string_building.hpp>                        // string_from
#include <fsm/text-io/Stream_id.hpp>                                // Stream_id

#include <string_view>
#include <utility>

namespace fabulous_support_machinery::console::_definitions {
    using   std::string_view,                       // <string_view>
            std::forward;                           // <utility>

    namespace os {
        extern void clear_screen();
        extern void output_to( Output_stream_id, in_<string_view> );
    }  // namespace os

    using os::clear_screen;
    using os::output_to;

    // Wrappers:
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
        d::clear_screen,
        d::output_to,
        d::output,
        d::output_err;
    }  // namespace exports
}  // namespace fabulous_support_machinery::console::_definitions

namespace fabulous_support_machinery::console   { using namespace _definitions::exports; }
