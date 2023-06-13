#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

// Example usage:
//
//     some_function( args... )
//         >> FSM_EXPECT( retval > 0 )
//         or FSM_FAIL( "some_function failed" );
//
// Or with $-macros from header <fsm/$-macros.hpp>:
//
//     some_function( args... )
//         >> $expect( retval > 0 )
//         or $fail( "some_function failed" );


#include <fsm/core/constructs/declarations/type_builders.hpp>        // in_

#include <functional>
#include <utility>

#define FSM_EXPECT( ... ) \
    ::fabulous_support_machinery::Expect_( \
        []( const auto retval ) -> bool { return (__VA_ARGS__); } \
        )

namespace fabulous_support_machinery::_definitions {
    using   std::function,          // <functional>
            std::move;              // <utility>

    template< class Checker_func >
    class Expect_
    {
        const Checker_func  m_is_success;
        
    public:
        Expect_( Checker_func checker ): m_is_success( move( checker ) ) {}

        template< class Value >
        auto denotes_success( in_<Value> value ) const
            -> bool
        { return m_is_success( value ); }
    };

    template< class Type, class Checker_func >
    constexpr auto operator>>( in_<Type> value, in_<Expect_<Checker_func>> check )
        -> bool
    { return check.denotes_success( value ); }

    namespace d = _definitions;
    namespace exports { using
        d::Expect_;
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery     { using namespace _definitions::exports; }
