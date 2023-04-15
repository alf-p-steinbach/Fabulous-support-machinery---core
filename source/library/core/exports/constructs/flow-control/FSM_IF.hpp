#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/failure-handling/FSM_STATIC_ASSERT.hpp>           // FSM_STATIC_ASSERT
#include <fsm/core/exports/meta-type/type-inspectors/compiletime-type-inspectors.hpp>   // is_same_

#define FSM_EXPANDED( ... )      __VA_ARGS__

#define FSM_IF_WITH( parenthesized_initializer, condition ) \
    if( \
        FSM_EXPANDED( parenthesized_initializer ); \
        fabulous_support_machinery::asserted_as_bool( condition ) \
        )
        
#define FSM_IF( condition ) \
    FSM_IF_WITH( (), condition )
    
namespace fabulous_support_machinery {
    
    template< class Type >
    constexpr auto asserted_as_bool( const Type v )
        -> bool
    {
        FSM_STATIC_ASSERT( is_same_<Type, bool> );
        return v;
    }

}  // namespace fabulous_support_machinery
