#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/wrapped/c_lib/stddef.hpp>        // ptrdiff_t, size_t

namespace fsm_definitions {
    namespace basic_type {

        using   Size        = ptrdiff_t;            // Signed.
        using   Index       = ptrdiff_t;            // Signed.

        static_assert( sizeof( Size ) == sizeof( size_t ) );    // May not hold for 16-bit embedded.
    }  // namespace basic_type
}  // namespace fsm_definitions

namespace fsm {
    inline namespace basic_type { using namespace fsm_definitions::basic_type; }
}  // namespace fsm
