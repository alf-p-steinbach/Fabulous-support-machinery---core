#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/declarations/type_builders.hpp>                                // in_
#include <fsm/core/exports/failure/detecting/FSM_STATIC_ASSERT.hpp>           // FSM_STATIC_ASSERT
#include <fsm/core/exports/meta-type/type-inspectors/compiletime-type-inspectors.hpp>   // is_integer_, is_signed_

namespace fabulous_support_machinery {
    
    template< class Integer, class Func >
    void repeat_times( const Integer n, in_<Func> f )
    {
        FSM_STATIC_ASSERT( is_integer_<Integer> );
        if constexpr( is_signed_<Integer> ) {
            if( n < 0 ) {
                return;
            }
        }

        for( Integer i = n; i != 0; --i ) {
            f();
        }
    }

}  // namespace fabulous_support_machinery
