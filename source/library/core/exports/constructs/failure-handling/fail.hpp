#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <stdexcept>
#include <string>

namespace fabulous_support_machinery::_definitions {
    using   std::runtime_error,
            std::string;

    template< class X >
    [[noreturn]]
    inline auto fail_( const string& message )
        -> bool
    { throw X( message ); }

    [[noreturn]]
    inline auto fail( const string& message )
        -> bool
    { fail_<runtime_error>( message ); }
    
    namespace d = _definitions;
    namespace exports { using
        d::fail_,
        d::fail;
    };
}  // namespace fabulous_support_machinery::_definitions;

namespace fabulous_support_machinery{ using namespace _definitions::exports; }
