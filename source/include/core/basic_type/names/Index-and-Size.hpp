#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/wrapped/c_lib/stddef.hpp>        // ptrdiff_t, size_t

namespace fsm_definitions {
    namespace basic_types {

        using   Size        = ptrdiff_t;            // Signed.
        using   Index       = ptrdiff_t;            // Signed.

        static_assert( sizeof( Size ) == sizeof( size_t ) );
    }  // namespace basic_types
}  // namespace fsm_definitions

namespace fsm {
    inline namespace basic_types { using namespace fsm_definitions::basic_types; }
}  // namespace fsm
