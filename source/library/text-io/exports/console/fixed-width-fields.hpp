#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

// TODO: clean up includes
#include <fsm/core/exports/support-for-collections/size-functions.hpp>      // int_size_of, int_capacity_of
#include <fsm/core/exports/constructs/declarations/FSM_ENABLE_IF.hpp>      // FSM_ENABLE_IF
#include <fsm/core/exports/text/encoding/u8/Code_point_iterator_.hpp>       // Code_point_iterator
#include <fsm/core/exports/text/sprintf-to-std-string.hpp>                  // unsafe::sprintf_to
#include <fsm/core/exports/text/unicode/monospaced-display-width.hpp>       // assumed_monospaced_display_width_of
#include <fsm/core/exports/constructs/declarations/type_builders.hpp>                    // in_
#include <fsm/text-io/exports/Stream_id.hpp>                                // Stream_id

#include <algorithm>
#include <iterator>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

#include <stddef.h>         // size_t
#include <stdio.h>          // snprintf

namespace fabulous_support_machinery::console::_definitions {
    namespace fsm = fabulous_support_machinery;
    using   std::max,                                   // <algorithm>
            std::prev,                                  // <iterator>
            std::string, std::to_string,                // <string>
            std::string_view,                           // <string_view>
            std::is_arithmetic_v,                       // <type_traits>
            std::forward, std::move, std::enable_if_t;  // <utility>

    inline auto display_width_of( const char32_t code )
        -> int
    {
        return unicode::assumed_monospaced_display_width_of( code );
        // TODO: take console behavior details into account.
        // A simplistic-heuristic could be: return 1 + (code >= 0x1100);
        // Actual return here is still a bit heuristic and accuracy depends on Unicode version.
    }

    inline auto display_width_of( in_<string_view> s )      // Necessarily imperfect, heuristic.
        -> int
    {
        // TODO: express in terms of a console-specific version of the single code point function.
        return unicode::assumed_monospaced_display_width_of( s );
    }

    class Text_with_display_width
    {
        string_view     m_text;
        int             m_display_width;

    public:
        Text_with_display_width( in_<string_view> s ):
            m_text( s ),
            m_display_width( display_width_of( s ) )
        {}

        auto sv() const -> string_view { return m_text; }
        auto display_width() const -> int { return m_display_width; }

        // TODO: leftcropped
        // TODO: ellipsis
        // TODO: copy policy as parameter

        void rightcrop_to_width( const int w )
        {
            if( m_display_width <= w ) {
                return;
            }

            const auto p_first      = m_text.data();
            const auto p_beyond     = p_first + m_text.size();
            const auto it_beyond    = u8::Code_point_iterator( p_beyond );

            for( auto it_back = prev( it_beyond ); true; --it_back ) {
                m_display_width -= display_width_of( it_back->cp_number() );
                const_<const char*> p_cropped_beyond = it_back.unit_iterator();
                if( p_cropped_beyond == p_first ) {
                    m_text = {};
                    return;
                } else if( m_display_width <= w ) {
                    m_text = string_view( p_first, p_cropped_beyond - p_first );
                    return;
                }
            }
            for( ;; ) {}        // Should never get here.
        }
    };  // class Text_with_display_width

    inline auto rightcropped_to_width( const int w, in_<string_view> s )
        -> Text_with_display_width
    {
        auto result = Text_with_display_width( s );
        result.rightcrop_to_width( w );
        return result;
    }

    inline auto left( const int w, in_<string_view> s, string&& buffer = "" )
        -> string
    {
        if( w <= 0 ) {
            return "";
        }
        const auto  cropped_s           = rightcropped_to_width( w, s );
        const int   text_display_width  = cropped_s.display_width();
        const int   n_spaces            = w - text_display_width;               // Guaranteed ≥ 0.

        buffer.reserve( cropped_s.sv().length() + n_spaces );
        buffer = cropped_s.sv();
        buffer.append( n_spaces, ' ' );
        return move( buffer );
    }

    template< class tp_Number, FSM_ENABLE_IF( is_arithmetic_v< tp_Number > ) >
    inline auto left( const int w, const tp_Number value )
        -> string
    { return left( w, to_string( value ) ); }   // TODO: replace `to_string`

    inline auto right( const int w, in_<string_view> s, string&& buffer = "" )
        -> string
    {
        if( w <= 0 ) {
            return "";
        }
        const auto  cropped_s           = rightcropped_to_width( w, s );        // TODO: left-cropped.
        const int   text_display_width  = cropped_s.display_width();
        const int   n_spaces            = w - text_display_width;               // Guaranteed ≥ 0.

        buffer.reserve( n_spaces + cropped_s.sv().length() );
        buffer.clear();
        buffer.append( n_spaces, ' ' );
        buffer += cropped_s.sv();
        return move( buffer );
    }
    
    template< class tp_Number, FSM_ENABLE_IF( is_arithmetic_v< tp_Number > ) >
    inline auto right( const int w, const tp_Number value )
        -> string
    { return right( w, to_string( value ) ); }                                  // TODO: replace `to_string`

    namespace d = _definitions;
    namespace exports{ using
        d::display_width_of,
        d::Text_with_display_width,
        d::rightcropped_to_width,
        d::left, d::right;
    }  // namespace exports
}  // namespace fabulous_support_machinery::console::_definitions

namespace fabulous_support_machinery::console   { using namespace _definitions::exports; }
