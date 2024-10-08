#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <cstdio>

namespace fsm_definitions {

    namespace input {

        class Line_reader
        {
        public:
            auto next( const int n_max_chars = 256 )
                -> string
            {
                const int chunk_size = 64;
                string result;
                for( ;; ) {

                }
            }
        };

        inline lines()
            -> Line_reader&
        {
            static Line_reader the_line_reader = {};
            return the_line_reader;
        }

        inline auto input_line( const int n_max_chars = 256 )
            -> string
        { return lines().next( n_max_chars ); }

    }  // namespace input
}  // namespace fsm_definitions

namespace fsm {
    inline namespace input { using namespace fsm_definitions::input; }
}  // namespace fsm
