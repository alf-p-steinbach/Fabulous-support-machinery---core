#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/headers/+std-cpp-language.hpp>

#include <fsm/core/headers/basic-types/Size+Index.hpp>                          // Index
#include <fsm/core/headers/constructs/declarations/type_builders.hpp>           // in_

#include <deque>
#include <queue>
#include <utility>

namespace fsm_definitions::queue_ops {
    namespace fsm = fabulous_support_machinery;
    using   fsm::Index,
            fsm::in_, fsm::ref_;
    using   std::deque,
            std::queue,
            std::move, std::forward;           // <utility>

    template< class Item, class Container = std::deque<Item>, class... Args >
    auto make_queue( Args&&... args )
        -> queue<Item, Container>
    {
        queue<Item, Container>  result;
        (result.push( forward<Args>( args ) ), ...);
        return result;
    }

    template< class Item, class Container >
    auto container_for( in_<queue<Item, Container>> q )
        -> const Container&
    {
        using Queue = queue<Item, Container>;
        struct Access: Queue { using Queue::c; };
        return q.*&Access::c;
    }

    template< class Item, class Container >
    auto item_at( const Index i, in_<queue<Item, Container>> q )
        -> const Item&
    { return container_for( q )[i]; }

    template< class Item, class Container >
    auto checked_item_at( const Index i, in_<queue<Item, Container>> q )
        -> const Item&
    { return container_for( q ).at( i ); }

    template< class Item, class Container >
    auto popped_front_of( ref_<queue<Item, Container>> q )
        -> Item
    {
        Item result = move( q.front() );
        q.pop();
        return result;
    }

    namespace x = queue_ops;
    namespace exports { using
        x::make_queue,
        x::container_for,
        x::item_at,
        x::checked_item_at,
        x::popped_front_of;
    }  // namespace exports
}  // namespace fsm_definitions::queue_ops

namespace fabulous_support_machinery{
    using namespace fsm_definitions::queue_ops::exports;

    // Not a simple equate because may need to be an extension of earlier declared namespace.
    namespace queue_ops {
        using namespace fsm_definitions::queue_ops::exports;
    }  // namespace exports
}  // namespace fabulous_support_machinery
