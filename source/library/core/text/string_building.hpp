#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/constructs/declarations/FSM_ENABLE_IF.hpp>   // FSM_ENABLE_IF
#include <fsm/core/constructs/declarations/type_builders.hpp>                 // in_

#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

namespace fabulous_support_machinery::string_building::_definitions {
    using namespace std::string_literals;
    using   std::string, std::to_string,    // <string>
            std::string_view,               // <string_view>
            std::is_arithmetic_v,           // <type_traits>
            std::forward, std::move;        // <utility>

    inline auto operator<<( string& destination, in_<string_view> source )
        -> string&
    { return destination.append( source ); }

    // TODO: overloads for numbers etc.

    template< class T, FSM_ENABLE_IF( is_arithmetic_v<T> ) >
    inline auto operator<<( string& destination, in_<T> value )
        -> string&
    {
        return destination.append( to_string( value ) );        // TODO: from_chars
    }

    template< class T >
    inline auto operator<<( string&& destination, in_<T> source )
        -> string&&
    { return move( destination << source ); }
    
    template< class... Args >
    inline auto string_from( string&& destination, Args&&... args )
        -> string&&
    { return move( (destination << ... << args) ); }
    
    template< class... Args >
    inline auto string_from( Args&&... args )
        -> string
    { return string_from( string(), forward<Args>( args )... ); }
    
    namespace d = _definitions;
    namespace exports { using
        d::operator<<,
        d::string_from;
    }  // namespace exports
}  // namespace fabulous_support_machinery::string_building::_definitions

namespace fabulous_support_machinery::string_building   { using namespace _definitions::exports; }
namespace fabulous_support_machinery                    { using string_building::string_from; }
