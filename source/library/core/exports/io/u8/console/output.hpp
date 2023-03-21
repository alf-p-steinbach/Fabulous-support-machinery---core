#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/type_builders.hpp>     // in_
#include <fsm/core/exports/io/u8/Stream_id.hpp>              // Stream_id

#include <string_view>
#include <utility>

namespace fabulous_support_machinery::console::_definitions {
    namespace fsm = fabulous_support_machinery;
    using   std::string_view,                       // <string_view>
            std::forward;                           // <utility>

    extern void clear_screen();
    extern void output_to( Output_stream_id, in_<string_view> );

    inline void output( in_<string_view> s )
    {
        output_to( Stream_id::out, s );
    }

    inline void output_err( in_<string_view> s )
    {
        output_to( Stream_id::err, s );
    }

    namespace d = _definitions;
    namespace exports{ using
        d::clear_screen, d::output_to,
        d::output, d::output_err;
    }  // namespace exports
}  // namespace fabulous_support_machinery::console::_definitions

namespace fabulous_support_machinery::console   { using namespace _definitions::exports; }
