#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/basic_type/Cardinal_int.hpp>             // Cint
#include <fsm/core/exception_handling/FSM_FAIL.hpp>         // now, $fail
#include <fsm/core/stream_io/put.hpp>                       // put
#include <fsm/core/text/trimming.hpp>                       // trimmed
#include <fsm/core/text/encoding/u8.hpp>                    // fsm::text::u8::*

#include <algorithm>

#include <cstdio>

namespace fsm_definitions {
    using   fsm::Cint,                  // basic_type/Cardinal_int.hpp
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
        constexpr   Cint    minimum_max_line_length     = text::u8::max_seq_length;
        constexpr   Cint    max_full_line_length        = 128*1024;

        struct Input_source{ enum Enum{ biological, machine }; };

        class Line_reader
        {
            FILE*           m_stream;
            Cint            m_max_line_length;

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
        };

        inline auto Line_reader::next() -> string
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
    }  // namespace stream_io
}  // namespace fsm_definitions

namespace fsm {
    inline namespace stream_io { using namespace fsm_definitions::stream_io; }
}  // namespace fsm
