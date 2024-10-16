#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/basic_type/names/C_str.hpp>
#include <utility>

namespace fsm_definitions {
    using   fsm::C_str;
    using   std::enable_if_t;       // <utility>

    namespace parameter_passing {
        template< bool condition >
        constexpr auto enabled_if_( C_str = nullptr )
            -> enable_if_t<condition, bool>
        { return true; }
    }  // namespace parameter_passing
}  // namespace fsm_definitions

namespace fsm {
    inline namespace parameter_passing { using namespace fsm_definitions::parameter_passing; }
}  // namespace fsm
