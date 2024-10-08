#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <cstdio>

namespace fsm_definitions {

    namespace input {

        auto input_line( const int n_max_chars = 256 )
            -> string
        {
            const int chunk_size = 64;
            string result;
            for( ;; ) {

            }
        }
    }  // namespace input
}  // namespace fsm_definitions

namespace fsm {
    inline namespace input { using namespace fsm_definitions::input; }
}  // namespace fsm
