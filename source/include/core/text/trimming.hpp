#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <fsm/core/parameter_passing/in_.hpp>
#include <fsm/core/type_builders.hpp>
#include <fsm/core/text/classifiers.hpp>

#include <string_view>

namespace fsm_definitions {
    using   fsm::const_,                // <type_builders.hpp>
            fsm::in_;                   // <in_.hpp>
    using   std::string_view;           // <string_view>

    namespace text {
        constexpr auto trimmed_start_of( in_<string_view> s )
            -> const char*      // A start pointer.
        {
            const_<const char*> p_beyond = s.data() + s.size();
            const char* p = s.data();
            while( p != p_beyond and is_ascii_whitespace( *p ) ) { ++p; }
            return p;
        }

        constexpr auto trimmed_end_of( in_<string_view> s )
            -> const char*      // A beyond pointer.
        {
            const_<const char*> p_start = s.data();
            if( s.empty() ) { return p_start; }
            const char* p = s.data() + s.size();
            for( ;; ) {
                --p;
                if( not is_ascii_whitespace( *p ) ) { return p + 1; }
                if( p == p_start ) { return p; }
            }
        }

        constexpr auto trimmed( in_<string_view> s )
            -> string_view
        {
            const_<const char*> p_start = trimmed_start_of( s );
            const_<const char*> p_beyond = trimmed_end_of( s );
            return string_view( p_start, p_beyond - p_start );
        }

    }  // namespace text
}  // namespace fsm_definitions

namespace fsm {
    inline namespace text{ using namespace fsm_definitions::text; }
}  // namespace fsm
