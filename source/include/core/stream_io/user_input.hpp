#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/stream_io/std_streams.hpp>

namespace fsm_definitions {
    using   fsm::stdin_lines;       // stream_io/std_streams.hpp

    namespace stream_io {

        inline auto input_line()
            -> string
        { return trimmed( stdin_lines().next() ); }

        inline auto input_line( in_<string_view> prompt )
            -> string
        {
            put( prompt );
            return input_line();
        }

    }  // namespace stream_io
}  // namespace fsm_definitions

namespace fsm {
    inline namespace stream_io { using namespace fsm_definitions::stream_io; }
}  // namespace fsm
