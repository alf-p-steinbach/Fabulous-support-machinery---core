#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <fsm/core/stream_io/put.hpp>
#include <fsm/core/text/trimming.hpp>

#include <cstdio>

namespace fsm_definitions {
    using   fsm::put,                   // <put.hpp>
            fsm::trimmed;               // <trimming.hpp>
    using   std::FILE;

    namespace input {
        struct Max_line_length{ int value; };
        constexpr auto n_max_chars_default = Max_line_length{ 256 };

        class Line_reader
        {
            FILE*       m_stream;

        public:
            Line_reader( const_<FILE*> stream = stdin ):
                m_stream( stream )
            {
                assert( m_stream );
            }

            auto next( const Max_line_length n_max_chars = n_max_chars_default )
                -> string
            {
                (void) n_max_chars;     // TODO: Impose limit
                // const int chunk_size = 64;
                string result;
                for( ;; ) {
                    const int ch_code = fgetc( m_stream );
                    // TODO: fail on EOF
                    if( ch_code == EOF or ch_code == '\n' ) {
                        break;
                    }
                    result += char( ch_code );
                }
                return result;
            }
        };

        inline auto stdin_lines()
            -> Line_reader&
        {
            static Line_reader the_line_reader = {};
            return the_line_reader;
        }

        inline auto full_input_line( const Max_line_length n_max_chars = n_max_chars_default )
            -> string
        { return stdin_lines().next( n_max_chars ); }

        inline auto full_input_line(
            in_<string_view>        prompt,
            const Max_line_length   n_max_chars = n_max_chars_default
            ) -> string
        {
            put( prompt );
            return full_input_line( n_max_chars );
        }

        inline auto input_line( const Max_line_length n_max_chars = n_max_chars_default )
            -> string
        { return trimmed( full_input_line( n_max_chars ) ); }

        inline auto input_line(
            in_<string_view>        prompt,
            const Max_line_length   n_max_chars = n_max_chars_default
            ) -> string
        {
            put( prompt );
            return input_line( n_max_chars );
        }
    }  // namespace input
}  // namespace fsm_definitions

namespace fsm {
    inline namespace input { using namespace fsm_definitions::input; }
}  // namespace fsm
