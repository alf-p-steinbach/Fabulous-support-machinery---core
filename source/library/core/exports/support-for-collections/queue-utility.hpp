#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/basic-types/Size+Index.hpp>       // Index
#include <fsm/core/exports/failure/detecting/hopefully.hpp>   // hopefully
#include <fsm/core/exports/failure/expressing/FSM_FAIL.hpp>    // FSM_FAIL_
#include <fsm/core/exports/constructs/declarations/type_builders.hpp>                // in_

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
        hopefully( size_t( i ) < q.size() ) or FSM_FAIL( "Out of range index" );
        using Queue = queue<Item, Allocator>;
        struct Access: Queue { using Queue::c; };
        return (q.*&Access::c)[i];
    }

    template< class Item, class Allocator >
    auto popped_front_of( queue<Item, Allocator>& q )
        -> Item
    {
        Item result = q.front();
        q.pop();
        return result;
    }

    template< class Item, class Allocator >
    auto popped_front_of( queue<Item, Allocator>&& q )
        -> Item
    { return popped_front_of( q ); }

    namespace d = _definitions;
    namespace exports { using
        d::item_at,
        d::popped_front_of;
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace _definitions::exports; }
