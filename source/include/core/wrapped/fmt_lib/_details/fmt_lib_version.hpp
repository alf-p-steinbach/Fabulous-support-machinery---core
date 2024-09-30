#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <fmt/core.h>       // FMT_VERSION
#include <string>

namespace fsm_definitions {
    using   std::string;
    
    namespace fmt_lib {

        struct Fmt_lib_version
        {
            int     major;
            int     minor;
            int     patch           = 0;
            
            static constexpr auto from_number( const long version_number ) noexcept
                -> Fmt_lib_version
            { return {version_number / 10000, (version_number/100) % 100, version_number % 100}; }

            constexpr auto number() const noexcept -> long { return (major*100 + minor)*100 + patch; }

            auto to_string() const -> string { return format( "{}.{}", major, minor ); }
            auto to_string_all() const -> string { return format( "{}.{}.{}", major, minor, patch ); }
        };

        const inline auto fmt_lib_version       = Fmt_lib_version::from_number( FMT_VERSION );
        const inline auto fmt_lib_description   = format( "{{fmt}} version {}", fmt_lib_version.to_string() );

    }  // namespace fmt_lib
}  // namespace fsm_definitions

namespace fsm {
    inline namespace fmt_lib{ using namespace fsm_definitions::fmt_lib; }
}  // namespace fsm

//FSM_USING_ORIGINAL_FMTLIB
