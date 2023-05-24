#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/headers/+std-cpp-language.hpp>

#include <iterator>     // std::(begin, end)

namespace fabulous_support_machinery::_definitions {

    template< class C >
    constexpr auto begin_of( C& c )
        -> auto
    { using std::begin; return begin( c ); }

    template< class C >
    constexpr auto end_of( C& c )
        -> auto
    { using std::end; return end( c ); }

    namespace d = _definitions;
    namespace exports { using
        d::begin_of,
        d::end_of;
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace _definitions::exports; }
