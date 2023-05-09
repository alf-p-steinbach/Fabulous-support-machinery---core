#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/basic-types/Size+Index.hpp>                  // Index
#include <fsm/core/exports/failure/detecting/hopefully.hpp>             // hopefully
#include <fsm/core/exports/failure/expressing/FSM_FAIL.hpp>             // FSM_FAIL_
#include <fsm/core/exports/constructs/declarations/type_builders.hpp>   // in_, ref_
#include <fsm/core/exports/support-for-collections/Iterator_pair_.hpp>  // Iterator_pair_

#include <deque>
#include <stack>
#include <utility>

#include <stddef.h>         // size_t

namespace fabulous_support_machinery::_definitions {
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
    auto popped_top_of( stack<Item, Container>& st )
        -> Item
    {
        Item result = move( st.top() );
        st.pop();
        return result;
    }

    namespace d = _definitions;
    namespace exports { using
        d::make_stack,
        d::container_for,
        d::item_at,
        d::checked_item_at,
        d::popped_top_of;
    }
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery{
    using namespace _definitions::exports;

    // Not a simple equate because may need to be an extension of earlier declared namespace.
    namespace stack_ops {
        using namespace _definitions::exports;
    }  // namespace exports

}  // namespace fabulous_support_machinery
