#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/stream_io/Line_reader.hpp>

namespace fsm_definitions {
    namespace stream_io {

        inline auto stdin_lines()
            -> Line_reader&
        {
            static auto the_line_reader = Line_reader( stdin );
            return the_line_reader;
        }

        inline auto full_input_line(
            const Max_line_length   max_line_length     = max_full_line_length_default
            ) -> string
        { (void) max_line_length;  return stdin_lines().next(); }  // TODO:

        inline auto full_input_line(
            in_<string_view>        prompt,
            const Max_line_length   max_line_length     = max_full_line_length_default
            ) -> string
        {
            put( prompt );
            return full_input_line( max_line_length );
        }

    }  // namespace stream_io
}  // namespace fsm_definitions

namespace fsm {
    inline namespace stream_io { using namespace fsm_definitions::stream_io; }
}  // namespace fsm
