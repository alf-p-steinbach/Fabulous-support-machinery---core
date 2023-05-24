#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/headers/+std-cpp-language.hpp>

#include <fsm/core/headers/constructs/declarations/FSM_ENABLE_IF.hpp>       // FSM_ENABLE_IF
#include <fsm/core/headers/meta-type/type-inspectors.hpp>                   // are_base_and_derived_

#include <stdexcept>
#include <string>
#include <type_traits>

namespace fabulous_support_machinery::_definitions {
    using   std::runtime_error,
            std::string,
            std::is_constructible_v;

    template< class X, class String, class... Args >
    [[noreturn]]
    inline auto fail_with_msg_as_string_( const String& s, const Args&... args )
        -> bool
    { throw X( static_cast<string>( s ), args... ); }

    template< class X, class First_arg, class... More_args >
    constexpr bool is_constructible_with_string_ = is_constructible_v<X, string, More_args...>;


    // Main functionality:

    template< class X, class... Args >
    [[noreturn]]
    inline auto fail_( const Args&... args )
        -> bool
    {
        if constexpr(
            not is_constructible_v<X, Args...> and is_constructible_with_string_<X, Args...>
            ) {
            fail_with_msg_as_string_<X>( args... );
        } else {
            throw X( args... );
        }
    }

    [[noreturn]]
    inline auto fail( const string& message ) -> bool { fail_<runtime_error>( message ); }

    // Convenience wrapper, in particular for calling with `std::string_view` argument:

    template< class String_type,
        FSM_ENABLE_IF( not are_base_and_derived_<string, Bare_<String_type>> )
        >
    [[noreturn]]
    inline auto fail( String_type&& message ) -> bool { fail( string( message ) ); }
    
    namespace d = _definitions;
    namespace exports { using
        d::fail_,
        d::fail;
    };
}  // namespace fabulous_support_machinery::_definitions;

namespace fabulous_support_machinery{ using namespace _definitions::exports; }
