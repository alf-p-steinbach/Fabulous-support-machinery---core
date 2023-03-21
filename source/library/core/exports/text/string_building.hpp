#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/declarations/FSM_ENABLE_IF_.hpp>   // FSM_ENABLE_IF_
#include <fsm/core/exports/constructs/type_builders.hpp>                 // in_

#include <string>
#include <string_view>
#include <type_traits>

namespace fabulous_support_machinery::string_building {
    using namespace std::string_literals;
    using   std::string, std::to_string,    // <string>
            std::string_view,               // <string_view>
            std::is_arithmetic_v,           // <type_traits>
            std::enable_if_t;               // <utility>

    inline auto operator<<( string& destination, in_<string_view> source )
        -> string&
    { return destination.append( source ); }

    template<
        class tp_Number,
        FSM_ENABLE_IF_( is_arithmetic_v< tp_Number > )
        >
    inline auto left( const int w, const tp_Number value )
        -> string
    { return left( w, to_string( value ) ); }

    template< class tp_T >
    inline auto operator<<( string&& destination, in_<tp_T> source )
        -> string&&
    { return move( destination << source ); }
}  // namespace fabulous_support_machinery::string_building
