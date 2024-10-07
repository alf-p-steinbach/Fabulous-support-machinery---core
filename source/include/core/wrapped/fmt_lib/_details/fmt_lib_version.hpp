#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <fmt/core.h>       // FMT_VERSION
#include <fsm/core/mixins/With_relops_from_compare_.hpp>
#include <fsm/core/parameter_passing/in_.hpp>
#include <string>

namespace fsm_definitions {
    using   fsm::in_, fsm::With_relops_from_compare_;
    using   std::string;
    
    namespace fmt_lib {

        struct Fmt_lib_version: With_relops_from_compare_<Fmt_lib_version>
        {
            using Self = Fmt_lib_version;

            int     major;
            int     minor;
            int     patch       = 0;

            constexpr Fmt_lib_version( const int _major, const int _minor, const int _patch = 0 ):
                major( _major ), minor( _minor ), patch( _patch )
            {}

            static constexpr auto from_number( const int version_number ) noexcept
                -> Fmt_lib_version
            { return {version_number / 10000, (version_number/100) % 100, version_number % 100}; }

            constexpr auto number() const noexcept -> int { return (major*100 + minor)*100 + patch; }

            auto to_string() const -> string { return format( "{}.{}", major, minor ); }
            auto to_string_all() const -> string { return format( "{}.{}.{}", major, minor, patch ); }

            static constexpr auto compare( in_<Self> a, in_<Self> b ) noexcept
                -> int
            { return a.number() - b.number(); }
        };

        const inline auto fmt_lib_version       = Fmt_lib_version::from_number( FMT_VERSION );
        const inline auto fmt_lib_description   = format( "{{fmt}} version {}", fmt_lib_version.to_string() );

    }  // namespace fmt_lib
}  // namespace fsm_definitions

namespace fsm {
    inline namespace fmt_lib{ using namespace fsm_definitions::fmt_lib; }
}  // namespace fsm

//FSM_USING_ORIGINAL_FMTLIB
