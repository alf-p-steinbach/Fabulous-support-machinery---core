#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/failure/x-classes/default_message_for_.hpp>

#include <stdexcept>
#include <string>

namespace fabulous_support_machinery::x::_definitions {
    using   std::runtime_error,     // <stdexcept>
            std::string;            // <string>
    
    struct End_of_file: runtime_error
    {
        using runtime_error::runtime_error;
        static constexpr auto& default_message = "End of file encountered immediately (no bytes).";
    };

    template<>
    inline auto default_message_for_<End_of_file>()
        -> string_view
    { return End_of_file::default_message; }

    namespace d = _definitions;
    namespace exports { using d::End_of_file; }
}  // namespace fabulous_support_machinery::x::_definitions

namespace fabulous_support_machinery::x     { using namespace _definitions::exports; }
