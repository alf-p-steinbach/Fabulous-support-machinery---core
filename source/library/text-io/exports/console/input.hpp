#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/text-io/exports/console/event-classes.hpp>
#include <fsm/text-io/exports/console/output.hpp>

#include <string>
#include <string_view>
#include <utility>


namespace fabulous_support_machinery::console::_definitions {
    using   std::string,            // <string>
            std::string_view,       // <string_view>
            std::move;              // <utility>

    namespace os {
        extern auto input_using_buffer( string&& ) -> string;
    }  // namespace os

#if 1
    using os::input_using_buffer;
#else
    inline auto input_using_buffer( string&& buffer )
        -> string
    {
        return "";
    }
#endif

    inline auto input()
        -> string
    { return input_using_buffer( "" ); }

    inline auto input( in_<string_view> prompt )
        -> string
    {
        output( prompt );
        return input_using_buffer( "" );
    }

    namespace d = _definitions;
    namespace exports{ using
        d::input_using_buffer,
        d::input;
    }  // namespace exports
}  // namespace fabulous_support_machinery::console::_definitions

namespace fabulous_support_machinery::console   { using namespace _definitions::exports; }
