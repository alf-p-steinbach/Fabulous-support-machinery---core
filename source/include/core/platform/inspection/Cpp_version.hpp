#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/basic_type/Cardinal_int.hpp>                         // Ꜿint
#include <fsm/core/mixins/With_relops_from_compare_.hpp>                // With_relops_from_compare_
#include <fsm/core/platform/inspection/cpp_version_macros.hpp>          // FSM_CPPxxx
#include <fsm/core/parameter_passing/data_flow_directions.hpp>          // in_

#include <string>

namespace fsm_definitions {
    using   fsm::in_, fsm::With_relops_from_compare_;
    using   std::string, std::to_string;        // <string>

    namespace platform {

        struct Cpp_version: With_relops_from_compare_<Cpp_version>
        {
            using Self = Cpp_version;

            Ꜿint    year;
            Ꜿint    month;              // 1-based.
            
            constexpr Cpp_version( const Ꜿint y, const Ꜿint m ): year( y ), month( m ) {}

            static constexpr auto from_number( const Ꜿint version_number ) noexcept
                -> Cpp_version
            { return {version_number / 100, version_number % 100}; }

            constexpr auto number() const noexcept -> Ꜿint { return 100*year + month; }

            constexpr auto informal_id() const noexcept -> Ꜿint { return year % 100; }

            auto to_string() const -> string { return "C++" + std::to_string( +informal_id() ); }

            static constexpr auto compare( in_<Self> a, in_<Self> b ) noexcept
                -> int
            {
                using fsm::cardinal_comparison::compare;
                return compare( a.number(), b.number() );
            }
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
