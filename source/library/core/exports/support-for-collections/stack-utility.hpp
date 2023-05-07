#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/basic-types/Size+Index.hpp>                  // Index
#include <fsm/core/exports/failure/detecting/hopefully.hpp>             // hopefully
#include <fsm/core/exports/failure/expressing/FSM_FAIL.hpp>             // FSM_FAIL_
#include <fsm/core/exports/constructs/declarations/type_builders.hpp>   // in_
#include <fsm/core/exports/support-for-collections/Iterator_pair_.hpp>  // Iterator_pair_

#include <stack>

#include <stddef.h>         // size_t

namespace fabulous_support_machinery::_definitions {
    using   std::stack;

    template< class Item, class Allocator >
    auto item_at( const Index i, in_<stack<Item, Allocator>> st )
        -> const Item&
    {
        using Stack = stack<Item, Allocator>;
        struct Access: Stack { using Stack::c; };
        return (st.*&Access::c)[i];
    }

    template< class Item, class Allocator >
    auto checked_item_at( const Index i, in_<stack<Item, Allocator>> st )
        -> const Item&
    {
        hopefully( size_t( i ) < st.size() ) or FSM_FAIL( "Out of range index" );
        return item_at( i, st );
    }
    
    template< class Item, class Allocator >
    auto all_of( in_<stack<Item, Allocator>> st )
        -> auto
    {
        using Stack = stack<Item, Allocator>;
        struct Access: Stack { using Stack::c; };
        return iterable_for::all_of( st.*&Access::c );
    }

    template< class Item, class Allocator >
    auto popped_top_of( stack<Item, Allocator>& st )
        -> Item
    {
        Item result = st.top();
        st.pop();
        return result;
    }

    namespace d = _definitions;
    namespace exports {
        inline namespace stack_ops {
            using
                d::item_at,
                d::checked_item_at,
                d::all_of,
                d::popped_top_of;
        }
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery
{
     using namespace _definitions::exports;
}
