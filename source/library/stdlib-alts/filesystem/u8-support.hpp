#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/constructs/declarations/type_builders.hpp>       // in_
#include <fsm/core/environment/properties/cpp-versions.hpp>         // FSM_CPPxxx
#include    <filesystem>
#include    <string>
#include    <string_view>

namespace fsm_definitions {
    namespace fsm = fabulous_support_machinery;
    namespace sfs = std::filesystem;

    using   fsm::in_,
            fsm::Bare_, fsm::is_same_;
    using   std::string,
            std::string_view;

    inline auto sfs_path_from( in_<string_view> path_spec )
        -> sfs::path
    { return sfs::u8path( path_spec ); }            // Note: `u8path` is deprecated in C++20.

    inline auto u8_from( in_<sfs::path> path )
        -> string
    {
        #if FSM_CPP_VERSION < FSM_CPP20
            return path.u8string();
        #else
            const auto result = path.u8string();    // Different types C++17 and C++20.
            return {result.begin(), result.end()};
        #endif
    }

    namespace d = fsm_definitions;
    namespace exports{ using
        d::sfs_path_from,
        d::u8_from;
    }  // namespace exports
}  // namespace fsm_definitions

namespace fabulous_support_machinery    { using namespace fsm_definitions::exports; }
