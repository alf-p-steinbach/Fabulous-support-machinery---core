#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/basic_type/names/Byte.hpp>

namespace fsm_definitions {
    using   fsm::bits_per_byte;         // <type.hpp>

    namespace basic_type {

        template< class Type >
        constexpr int bits_per_   = sizeof( Type )*bits_per_byte;

    }  // namespace basic_type
}  // namespace fsm_definitions

namespace fsm {
    inline namespace basic_type{ using namespace fsm_definitions::basic_type; }
}  // namespace fsm
