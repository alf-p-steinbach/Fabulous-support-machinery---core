#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <stdexcept>

#include <string>

namespace fabulous_support_machinery::x::_definitions {
    using   std::runtime_error;     // <stdexcept>
    
    struct End_of_file: runtime_error
    {
        using runtime_error::runtime_error;
        
        // TODO: traits function instead of
        static constexpr auto& default_message = "End of file encountered immediately (no bytes).";
    };

    namespace d = _definitions;
    namespace exports { using d::End_of_file; }
}  // namespace fabulous_support_machinery::x::_definitions

namespace fabulous_support_machinery::x     { using namespace _definitions::exports; }
