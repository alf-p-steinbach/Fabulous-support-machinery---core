#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/basic-types/Size+Index.hpp>                  // Index
#include <fsm/core/exports/failure/detecting/hopefully.hpp>             // hopefully
#include <fsm/core/exports/failure/expressing/FSM_FAIL.hpp>             // FSM_FAIL_
#include <fsm/core/exports/constructs/declarations/type_builders.hpp>   // in_
#include <fsm/core/exports/support-for-collections/Iterator_pair_.hpp>  // Iterator_pair_

#include <queue>
#include <stdexcept>

#include <stddef.h>         // size_t

namespace fabulous_support_machinery::_definitions {
    using   std::queue,             // <queue>
            std::out_of_range;      // <stdexcept>
    
    template< class Item, class Allocator >
    auto item_at( const Index i, in_<queue<Item, Allocator>> q )
        -> const Item&
    {
        using Queue = queue<Item, Allocator>;
        struct Access: Queue { using Queue::c; };
        return (q.*&Access::c)[i];
    }

    template< class Item, class Allocator >
    auto checked_item_at( const Index i, in_<queue<Item, Allocator>> q )
        -> const Item&
    {
        hopefully( size_t( i ) < q.size() ) or FSM_FAIL( "Out of range index" );
        return item_at( i, q );
    }

    template< class Item, class Allocator >
    auto all_of( in_<queue<Item, Allocator>> q )
        -> auto
    {
        using Queue = queue<Item, Allocator>;
        struct Access: Queue { using Queue::c; };
        return iterable_for::all_of( q.*&Access::c );
    }

    template< class Item, class Allocator >
    auto popped_front_of( queue<Item, Allocator>& q )
        -> Item
    {
        Item result = q.front();
        q.pop();
        return result;
    }

    namespace d = _definitions;
    namespace exports {
        inline namespace queue_ops {
            using
                d::item_at,
                d::checked_item_at,
                d::all_of,
                d::popped_front_of;
        }
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace _definitions::exports; }
