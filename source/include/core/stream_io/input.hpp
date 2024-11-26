#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/parameter_passing/data_flow_directions.hpp>      // in_
#include <fsm/core/stream_io/from_user.hpp>                         // stream_io::from_user::*

namespace fsm_definitions {
    using   fsm::in_;

    using Sv = std::string_view;

    namespace stream_io {
        inline auto input() -> string { return from_user::tokens(); }
        inline auto input( in_<Sv> prompt ) -> string { return from_user::tokens( prompt ); }
    }  // namespace stream_io
}  // namespace fsm_definitions

namespace fsm {
    inline namespace stream_io { using namespace fsm_definitions::stream_io; }
}  // namespace fsm
