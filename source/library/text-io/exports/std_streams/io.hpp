﻿#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/declarations/type_builders.hpp>            // in_
#include <fsm/core/exports/failure/x-classes/End_of_file.hpp>       // End_of_file
#include <fsm/text-io/exports/Stream_id.hpp>                        // Output_stream_id

#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

namespace fabulous_support_machinery::std_streams::_definitions {
    using   std::string,            // <string>
            std::string_view,       // <string_view>
            std::move;

    extern auto input_using_buffer( string&& buffer ) -> string;
    extern void output_to( const Output_stream_id stream_id, in_<string_view> s );

    inline auto input() -> string                   { return input_using_buffer( "" ); }
    inline void output( in_<string_view> s )        { output_to( Stream_id::out, s ); }
    inline void output_err( in_<string_view> s )    { output_to( Stream_id::err, s ); }

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
