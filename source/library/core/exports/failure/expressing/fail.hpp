#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/declarations/FSM_ENABLE_IF.hpp>       // FSM_ENABLE_IF
#include <fsm/core/exports/meta-type/type-inspectors.hpp>                   // are_derived_and_base_

#include <stdexcept>
#include <string>

namespace fabulous_support_machinery::_definitions {
    using   std::runtime_error,
            std::string;

    // Main functionality:

    template< class X >
    [[noreturn]]
    inline auto fail_( const string& message ) -> bool { throw X( message ); }

    [[noreturn]]
    inline auto fail( const string& message ) -> bool { fail_<runtime_error>( message ); }


    // Convenience wrappers, in particular for calling with `std::string_view` argument:

    template< class X, class String_type,
        FSM_ENABLE_IF( not are_derived_and_base_<Bare_<String_type>, string> )
        >
    [[noreturn]]
    inline auto fail_( String_type&& message ) -> bool { fail_<X>( string( message ) ); }

    template< class String_type,
        FSM_ENABLE_IF( not are_derived_and_base_<Bare_<String_type>, string> )
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
