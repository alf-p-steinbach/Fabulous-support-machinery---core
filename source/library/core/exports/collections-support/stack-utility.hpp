#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/basic-types/size-types.hpp>       // Index
#include <fsm/core/exports/constructs/failure-handling/hopefully.hpp>   // hopefully
#include <fsm/core/exports/constructs/failure-handling/FSM_FAIL.hpp>    // FSM_FAIL_
#include <fsm/core/exports/constructs/type_builders.hpp>                // in_

#include <stack>

#include <stddef.h>         // size_t

namespace fabulous_support_machinery::_definitions {
    using   std::stack;

    template< class Item, class Allocator >
    auto item_at( const Index i, in_<stack<Item, Allocator>> st )
        -> const Item&
    {
        hopefully( size_t( i ) < st.size() ) or FSM_FAIL( "Out of range index" );
        using Stack = stack<Item, Allocator>;
        struct Access: Stack { using Stack::c; };
        return (st.*&Access::c)[i];
    }
    
    template< class Item, class Allocator >
    auto popped_top_of( stack<Item, Allocator>& st )
        -> Item
    {
        Item result = st.top();
        st.pop();
        return result;
    }

    template< class Item, class Allocator >
    auto popped_top_of( stack<Item, Allocator>&& st )
        -> Item
    { return popped_top_of( st ); }

    namespace d = _definitions;
    namespace exports { using
        d::item_at,
        d::popped_top_of;
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace _definitions::exports; }
