#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/headers/+std-cpp-language.hpp>

#include <fsm/core/headers/constructs/declarations/type_builders.hpp>    // in_
#include <fsm/text-io/headers/Stream_id.hpp>                // Stream_id

namespace fabulous_support_machinery::std_streams::_definitions {
    
    extern auto is_console_stream( Stream_id ) -> bool;
    
    namespace exports { using _definitions::is_console_stream; }
}  // namespace fabulous_support_machinery::std_streams::_definitions

namespace fabulous_support_machinery::std_streams { using namespace _definitions::exports; }
