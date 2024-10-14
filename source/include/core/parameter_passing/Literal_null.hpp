#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

// `Literal_null` can be used as a parameter type for specializing the case of
// literal 0 as argument. Only literal `0` is accepted as constructor argument.
// In particular, `nullptr` as argument causes compilation error.
    
#include <fsm/core/parameter_passing/enabled_if_.hpp>

#include <type_traits>

namespace fsm_definitions {
    using   std::is_integral_v;         // <type_traits>

    namespace parameter_passing {

        class Literal_null
        {
            struct Anon {};

        public:
            constexpr Literal_null() {}

            template< class Arg, bool = enabled_if_< not is_integral_v<Arg> >() >
            constexpr Literal_null( Arg&& ) = delete;
            
            constexpr Literal_null( Anon* ) {}
        };

        inline constexpr auto null = Literal_null();

    }
}  // namespace fsm_definitions


namespace fsm {
    inline namespace parameter_passing { using namespace fsm_definitions::parameter_passing; }
}  // namespace fsm
