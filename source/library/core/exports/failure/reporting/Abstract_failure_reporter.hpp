#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/declarations/type_builders.hpp>                // in_
#include <fsm/core/exports/misc/support-for-collections/size-functions.hpp>  // is_empty
#include <fsm/core/exports/meta-type/class-kinds/Polymorphic.hpp>       // Polymorphic

#include <exception>
#include <string>
#include <string_view>

namespace fabulous_support_machinery::_definitions {
    using   std::exception,         // <exception>
            std::string,            // <string>
            std::string_view;       // <stringview>

    struct Abstract_failure_reporter: Polymorphic
    {
        virtual void output( in_<string_view> text ) const = 0;

        virtual void report( in_<string_view> text ) const
        {
            const auto s =  string( is_empty( text )? "No failure information available." : text );
            output( string() + "!" + s + "\n" );
        }

        virtual void report_unexpected() const
        {
            report( "An unexpected failure (a non-standard exception was thrown)." );
        }

        virtual void report( in_<exception> x ) const
        {
            // TODO: nested exceptions
            // TODO: exception name
            report( x.what() );
        }
    };

    // namespace d = _definitions;
    namespace exports { using
        d::Abstract_failure_reporter;
    }  // namespace exports
}  // namespace fabluous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace _definitions::exports; }
