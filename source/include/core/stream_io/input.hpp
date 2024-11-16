#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/basic_type/Cardinal_int.hpp>             // Cint
#include <fsm/core/exception_handling/FSM_FAIL.hpp>         // now, $fail
#include <fsm/core/stream_io/put.hpp>                       // put
#include <fsm/core/text/trimming.hpp>                       // trimmed
#include <fsm/core/text/encoding/u8.hpp>                    // fsm::text::u8::*

#include <cstdio>

namespace fsm_definitions {
    using   fsm::Cint,                  // basic_type/Cardinal_int.hpp
            fsm::now,                   // exception_handling/FSM_FAIL.hpp
            fsm::put,                   // stream_io/put.hpp
            fsm::trimmed;               // text/trimming.hpp

    using   std::FILE;

    namespace input {
        struct Max_line_length{ Cint value;  operator Cint() const { return value; } };

        constexpr auto minimum_max_line_length          = Max_line_length{ text::u8::max_seq_length };
        constexpr auto max_line_length_default          = Max_line_length{ 256 };
        constexpr auto max_full_line_length_default     = Max_line_length{ 16*1024 };

        class Line_reader
        {
            FILE*           m_stream;
            Cint            m_max_line_length;

        public:
            Line_reader(
                const_<FILE*>           stream          = stdin,
                const Max_line_length   max_line_length = max_line_length_default
                ):
                m_stream( stream ),
                m_max_line_length( max_line_length )
            {
                assert( m_stream );
                assert( m_max_line_length > minimum_max_line_length );
            }

            auto next() -> string
            {
                // TODO: Impose limit
                // const int chunk_size = 64;
                string result;
                for( ;; ) {
                    const int ch_code = fgetc( m_stream );
                    if( ch_code == EOF or ch_code == '\n' ) {
                        break;
                    }
                    result += char( ch_code );
                }
                const bool immediate_eof = (result == "" and feof( m_stream ));
                now( not immediate_eof ) or $fail( "Stream input encountered logical EOF immediately." );
                return result;
            }
        };

        inline auto stdin_lines()
            -> Line_reader&
        {
            static Line_reader the_line_reader = {};
            return the_line_reader;
        }

        inline auto full_input_line(
            const Max_line_length max_line_length = max_full_line_length_default
            ) -> string
        { (void) max_line_length;  return stdin_lines().next(); }  // TODO:

        inline auto full_input_line(
            in_<string_view>        prompt,
            const Max_line_length   max_line_length = max_full_line_length_default
            ) -> string
        {
            put( prompt );
            return full_input_line( max_line_length );
        }

        inline auto input_line()
            -> string
        { return trimmed( stdin_lines().next() ); }

        inline auto input_line( in_<string_view> prompt )
            -> string
        {
            put( prompt );
            return input_line();
        }
    }  // namespace input
}  // namespace fsm_definitions

namespace fsm {
    inline namespace input { using namespace fsm_definitions::input; }
}  // namespace fsm
