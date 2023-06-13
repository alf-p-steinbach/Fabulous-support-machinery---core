#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/failure/x-classes/default_message_for_.hpp>

#include <stdexcept>
#include <string>

namespace fsm_definitions::x {
    namespace fsm = fabulous_support_machinery;
    using   fsm::x::default_message_for_;
    using   std::runtime_error,     // <stdexcept>
            std::string;            // <string>
    
    struct End_of_file: runtime_error
    {
        using runtime_error::runtime_error;
        static constexpr auto& default_message = "End of file encountered immediately (no input bytes).";
    };

    template<>
    inline auto default_message_for_<End_of_file>()
        -> string_view
    { return End_of_file::default_message; }

    namespace d = x;
    namespace exports { using d::End_of_file; }
}  // namespace fsm_definitions::x

namespace fabulous_support_machinery{
    namespace x{ using namespace fsm_definitions::x::exports; }
}  // namespace fabulous_support_machinery{

