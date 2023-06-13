#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/constructs/declarations/type_builders.hpp>            // const_

#include <string>
#include <string_view>

#include <assert.h>

namespace fabulous_support_machinery::text::_definitions {
    using   std::basic_string, std::char_traits,        // <string>
            std::basic_string_view;                     // <string_view>
    
    template< class tp_Char >
    class C_string_view_:
        public basic_string_view<tp_Char>
    {
    public:
        using Char      = tp_Char;
        using Base      = basic_string_view<Char>;
        using Traits    = char_traits<Char>;

        constexpr C_string_view_(
            const_<const Char*>     s,
            const int               length  = -1
            ):
            Base( s, (length >= 0? length : static_cast<int>( Traits::length( s ) )) - 1 )
        {
            assert( s[length] == Char( 0 ) );
        }
        
        C_string_view_( in_<basic_string<Char>> s ): Base( s ) {}

        using   Base::data;

        constexpr auto c_str() const -> const Char* { return data(); }
    };  // class C_string_view_

    using C_string_view         = C_string_view_<char>;
    using Wide_c_string_view    = C_string_view_<wchar_t>;
    
    namespace d = _definitions;
    namespace exports{ using
        d::C_string_view_,
        d::C_string_view,
        d::Wide_c_string_view;
    }  // namespace exports
}  // namespace fabulous_support_machinery::text::_definitions

namespace fabulous_support_machinery::text  { using namespace _definitions::exports; }
