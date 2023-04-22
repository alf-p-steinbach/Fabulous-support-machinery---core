#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

// `Literal_null` can be used as a parameter type for specializing the case of
// literal 0 as argument. Only literal `0` is accepted as constructor argument.
// In particular, `nullptr` is not accepted (causes compilation error).
    
#include <fsm/core/exports/constructs/declarations/FSM_ENABLE_IF.hpp>
#include <fsm/core/exports/meta-type/type-inspectors.hpp>  // is_builtin_integral_type_

#include <type_traits>

namespace fabulous_support_machinery {
    
    class Literal_null
    {
        struct Anon {};
        Literal_null() = delete;

    public:
        template< class Arg, FSM_ENABLE_IF( not is_builtin_integral_type_<Arg> ) >
        constexpr Literal_null( Arg&& ) = delete;
        
        constexpr Literal_null( Anon* ) {}
    };

}  // namespace fabulous_support_machinery
