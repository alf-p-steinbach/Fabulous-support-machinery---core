#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

namespace fsm_definitions {
    namespace basic_type {

        template< class Type >
        constexpr bool is_byte_ = (sizeof( Type ) == 1);

    }  // namespace basic_type
}  // namespace fsm_definitions

namespace fsm {
    inline namespace basic_type{ using namespace fsm_definitions::basic_type; }
}  // namespace fsm
