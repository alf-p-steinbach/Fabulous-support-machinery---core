#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/parameter_passing/data_flow_directions.hpp>      // in_
#include <fsm/core/stream_io/Line_reader.hpp>                       // Line_reader

namespace fsm_definitions {
    using   fsm::in_;

    using Sv = std::string_view;

    namespace stream_io { namespace from_user {
        constexpr   Cint    max_line_length     = 256;

        inline auto lines()
            -> Line_reader&
        {
            static auto the_line_reader = Line_reader( stdin, With_max_line_length{ max_line_length } );
            return the_line_reader;
        }

        inline namespace basic {
            inline auto full_line()
                -> string
            { return lines().next(); }  // TODO:

            inline auto raw_line()
                -> string
            { return lines().next(); }

            inline auto line()
                -> string
            { return trimmed( raw_line() ); }       // TODO: "as tokens", removing consecutive whitespaces
        }  // inline namespace basic

        template< class Input_func >
        inline auto response_to( in_<Sv> prompt, in_<Input_func> get )
            -> auto
        {
            put( prompt );
            return get();
        }

        inline auto full_line( in_<Sv> prompt ) -> string   { return response_to( prompt, basic::full_line ); }
        inline auto raw_line( in_<Sv> prompt )  -> string   { return response_to( prompt, basic::raw_line ); }
        inline auto line( in_<Sv> prompt )      -> string   { return response_to( prompt, basic::line ); }
    } }  // namespace stream_io / namespace from_user

    namespace stream_io {
        inline auto input() -> string { return from_user::line(); }
        inline auto input( in_<string_view> prompt ) -> string { return from_user::line( prompt ); }
    }  // namespace stream_io
}  // namespace fsm_definitions

namespace fsm {
    inline namespace stream_io { using namespace fsm_definitions::stream_io; }
}  // namespace fsm
