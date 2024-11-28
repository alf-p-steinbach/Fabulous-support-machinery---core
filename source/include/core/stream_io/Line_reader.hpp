#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/basic_type/Cardinal_int.hpp>                 // Cint
#include <fsm/core/collections/support/remove_buffer_of.hpp>    // remove_buffer_of
#include <fsm/core/exception_handling/FSM_FAIL.hpp>             // now, $fail
#include <fsm/core/stream_io/put.hpp>                           // put
#include <fsm/core/text/trimming.hpp>                           // trimmed
#include <fsm/core/text/encoding/u8.hpp>                        // fsm::text::u8::*

#include <algorithm>

#include <cstdio>

namespace fsm_definitions {
    namespace u8 = fsm::text::u8;

    using   fsm::Cint,                  // basic_type/Cardinal_int.hpp
            fsm::remove_buffer_of,      // collections/support/remove_buffer_of
            fsm::now,                   // exception_handling/FSM_FAIL.hpp
            fsm::put,                   // stream_io/put.hpp
            fsm::trimmed;               // text/trimming.hpp

    using   std::max;           // <algorithm>
    using   std::FILE;          // <cstdio>

    namespace stream_io {
        // Parameter type.
        struct With_max_line_length{ Cint value;  operator Cint() const { return value; } };

        // Reasonable max line length may be different for interactive versus file input. In particular
        // a Java exception message can run til several KB. A human would never type that interacively.
        // These line lengths are measured in Unicode code points.
        constexpr   Cint    minimum_max_line_length     = text::u8::max_seq_length;
        constexpr   Cint    max_full_line_length        = 128*1024;

        class Line_reader
        {
            FILE*           m_stream;
            Cint            m_max_line_length;
            string          m_retained_data;        // Holds data from too long line.

        public:
            explicit Line_reader(
                const_<FILE*>               stream,
                const With_max_line_length  max_line_length
                ):
                m_stream( stream ),
                m_max_line_length( max( minimum_max_line_length, max_line_length.value ) )
            {
                assert( m_stream );
            }

            inline auto next() -> string;
            inline auto full_long_line() -> string;
        };

        inline auto Line_reader::next() -> string
        {
            // TODO: const int chunk_size = 64; ?
            remove_buffer_of( m_retained_data );
            string result;
            try {
                Cint n_codepoints = 0;
                for( ;; ) {
                    const int ch_code = fgetc( m_stream );
                    if( ch_code == EOF or ch_code == '\n' ) {
                        break;
                    }
                    result += char( ch_code );
                    n_codepoints += u8::is_seq_start( ch_code );
                    now( n_codepoints <= m_max_line_length )
                        or $fail( "Too long input line (more than {} Unicode code points).", +m_max_line_length );
                }
            } catch( ... ) {        // TODO: exception type
                m_retained_data = move( result );
                throw;
            }
            const bool immediate_eof = (result == "" and feof( m_stream ));
            now( not immediate_eof ) or $fail( "Stream input encountered logical EOF immediately." );
            return result;
        }

        inline auto Line_reader::full_long_line() -> string
        {
            return move( m_retained_data );     // TODO: implement for real.
        }
    }  // namespace stream_io
}  // namespace fsm_definitions

namespace fsm {
    inline namespace stream_io { using namespace fsm_definitions::stream_io; }
}  // namespace fsm
