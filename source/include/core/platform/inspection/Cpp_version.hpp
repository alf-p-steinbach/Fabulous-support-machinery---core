#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <fsm/core/mixins/With_relops_from_compare_.hpp>
#include <fsm/core/platform/inspection/cpp_version_macros.hpp>
#include <fsm/core/parameter_passing/in_.hpp>

#include <string>

namespace fsm_definitions {
    using   fsm::in_, fsm::With_relops_from_compare_;
    using   std::string, std::to_string;        // <string>

    namespace platform {

        struct Cpp_version: With_relops_from_compare_<Cpp_version>
        {
            using Self = Cpp_version;

            int     year;
            int     month;              // 1-based.
            
            constexpr Cpp_version( const int y, const int m ): year( y ), month( m ) {}

            static constexpr auto from_number( const int version_number ) noexcept
                -> Cpp_version
            { return {version_number / 100, version_number % 100}; }

            constexpr auto number() const noexcept -> int { return 100*year + month; }

            constexpr auto informal_id() const noexcept -> int { return year % 100; }

            auto to_string() const -> string { return "C++" + std::to_string( informal_id() ); }

            static constexpr auto compare( in_<Self> a, in_<Self> b ) noexcept
                -> int
            { return a.number() - b.number(); }
        };

        static_assert( FSM_CPP98 == FSM_CPP03 );
        constexpr auto cpp_version  = Cpp_version::from_number( FSM_CPP_VERSION );
        constexpr auto cpp98    = Cpp_version::from_number( FSM_CPP98 );
        constexpr auto cpp03    = Cpp_version::from_number( FSM_CPP03 );
        constexpr auto cpp11    = Cpp_version::from_number( FSM_CPP11 );
        constexpr auto cpp14    = Cpp_version::from_number( FSM_CPP14 );
        constexpr auto cpp17    = Cpp_version::from_number( FSM_CPP17 );
        constexpr auto cpp20    = Cpp_version::from_number( FSM_CPP20 );
        constexpr auto cpp23    = Cpp_version::from_number( FSM_CPP23 );

    }  // namespace platform
}  // namespace fsm_definitions

namespace fsm {
    inline namespace platform { using namespace fsm_definitions::platform; }
}  // namespace fsm
