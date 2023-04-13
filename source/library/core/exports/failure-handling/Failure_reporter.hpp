#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/type_builders.hpp>     // in_

#include <exception>
#include <string_view>

namespace fabulous_support_machinery::_definitions {
    using   std::exception,         // <exception>
            std::string_view;       // <stringview>

    struct Failure_reporter
    {
        virtual ~Failure_reporter() {}

        virtual void operator()( in_<string_view> text ) const = 0;

        virtual void operator()( in_<exception> x ) const
        {
            // TODO: nested exceptions
            // TODO: exception name
            operator()( x.what() );
        }
        
        virtual void operator()() const
        {
            operator()( "An unexpected failure (a non-standard exception was thrown)." );
        }
    };

    // namespace d = _definitions;
    namespace exports { using
        d::Failure_reporter;
    }  // namespace exports
}  // namespace fabluous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace _definitions::exports; }
