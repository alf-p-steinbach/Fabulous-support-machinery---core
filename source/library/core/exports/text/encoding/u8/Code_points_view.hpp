﻿#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/text/encoding/u8/Code_point_iterator_.hpp>

#include <iterator>

namespace fabulous_support_machinery::u8::_definitions {
    using   std::distance;      // <iterator>
    
    class Code_points_view:
        public Iterator_pair_< Code_point_iterator >
    {
    public:
        Code_points_view( in_<string_view> s ):
            Iterator_pair_< Code_point_iterator >( to_code_point_iterators( s ) )
        {}
        
        auto n_bytes() const
            -> int
        { return static_cast<int>( distance( begin().unit_iterator(), end().unit_iterator() ) ); }

        auto char_pointer() const
            -> const char*
        { return begin().unit_iterator(); }
        
        auto sv() const     -> string_view  { return string_view( char_pointer(), n_bytes() ); }
        auto str() const    -> string       { return string( char_pointer(), n_bytes() ); }
    };

    namespace d = _definitions;
    namespace exports { using
        d::Code_points_view;
    }  // namespace exports
}  // namespace fabulous_support_machinery::u8::_definitions

namespace fabulous_support_machinery::u8 { using namespace _definitions; }
