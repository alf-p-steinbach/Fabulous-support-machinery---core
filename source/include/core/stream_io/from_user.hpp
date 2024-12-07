#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/parameter_passing/data_flow_directions.hpp>      // in_
#include <fsm/core/stream_io/Line_reader.hpp>                       // Line_reader
#include <fsm/core/stream_io/output.hpp>                            // Line_reader

namespace fsm_definitions {
    using   fsm::in_,                           // parameter_passing/data_flow/directions.hpp
            fsm::output;                        // stream_io/output.hpp

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

            inline auto tokens()
                -> string
            { return trimmed( raw_line() ); }       // TODO: "as tokens", removing consecutive whitespaces
        }  // inline namespace basic

        template< class Input_func >
        inline auto response_to( in_<Sv> prompt, in_<Input_func> get )
            -> auto
        {
            output( prompt );
            return get();
        }

        inline auto full_line( in_<Sv> prompt ) -> string   { return response_to( prompt, basic::full_line ); }
        inline auto raw_line( in_<Sv> prompt )  -> string   { return response_to( prompt, basic::raw_line ); }
        inline auto tokens( in_<Sv> prompt )    -> string   { return response_to( prompt, basic::tokens ); }
    } }  // namespace stream_io / namespace from_user
}  // namespace fsm_definitions

namespace fsm {
    inline namespace stream_io { using namespace fsm_definitions::stream_io; }
}  // namespace fsm
