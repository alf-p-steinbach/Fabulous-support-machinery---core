#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/constructs/introspection/name_of_.hpp>

#include <string>
#include <string_view>

namespace fsm_definitions::x {
    namespace fsm = fabulous_support_machinery;
    using   fsm::name_of_;
    using   std::string,            // <string>
            std::string_view;       // <string_view>
    
    template< class X >
    auto default_message_for_()
        -> string_view
    {
        static const string msg = name_of_<X>();
        return msg;
    }

    namespace d = x;
    namespace exports { using d::default_message_for_; }
}  // namespace fsm_definitions::x

namespace fabulous_support_machinery
{
    namespace x { using namespace fsm_definitions::x::exports; }
}
