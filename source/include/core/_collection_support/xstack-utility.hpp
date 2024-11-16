#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/types/fundamental/Size+Index.hpp>                          // Index
#include <fsm/core/constructs/declarations/type_builders.hpp>           // in_, ref_

#include <deque>
#include <stack>
#include <utility>

namespace fsm_definitions::stack_ops {
    namespace fsm = fabulous_support_machinery;
    using   fsm::Index,
            fsm::in_, fsm::ref_;
    using   std::deque,
            std::stack,
            std::move, std::forward;        // <utility>

    template< class Item, class Container = std::deque<Item>, class... Args >
    auto make_stack( Args&&... args )
        -> stack<Item, Container>
    {
        stack<Item, Container>  result;
        (result.push( forward<Args>( args ) ), ...);
        return result;
    }

    template< class Item, class Container >
    auto container_for( in_<stack<Item, Container>> st )
        -> const Container&
    {
        using Stack = stack<Item, Container>;
        struct Access: Stack { using Stack::c; };
        return st.*&Access::c;
    }

    template< class Item, class Container >
    auto item_at( const Index i, in_<stack<Item, Container>> st )
        -> const Item&
    { return container_for( st )[i]; }

    template< class Item, class Container >
    auto checked_item_at( const Index i, in_<stack<Item, Container>> st )
        -> const Item&
    { return container_for( st ).at( i ); }
    
    template< class Item, class Container >
    auto popped_top_of( ref_<stack<Item, Container>> st )
        -> Item
    {
        Item result = move( st.top() );
        st.pop();
        return result;
    }

    namespace x = stack_ops;
    namespace exports { using
        x::make_stack,
        x::container_for,
        x::item_at,
        x::checked_item_at,
        x::popped_top_of;
    }
}  // namespace fsm_definitions::stack_ops

namespace fabulous_support_machinery{
    using namespace fsm_definitions::stack_ops::exports;

    // Not a simple equate because may need to be an extension of earlier declared namespace.
    namespace stack_ops {
        using namespace fsm_definitions::stack_ops::exports;
    }  // namespace exports
}  // namespace fabulous_support_machinery
