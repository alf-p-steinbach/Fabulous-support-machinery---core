#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <iterator>     // std::(begin, end)

namespace fabulous_support_machinery{

    template< class C >
    constexpr auto begin_of( C& c )
        -> auto
    { using std::begin; return begin( c ); }

    template< class C >
    constexpr auto end_of( C& c )
        -> auto
    { using std::end; return end( c ); }

}  // namespace fabulous_support_machinery
