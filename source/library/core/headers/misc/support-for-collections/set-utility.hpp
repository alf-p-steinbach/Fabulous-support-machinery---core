#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/headers/+std-cpp-language.hpp>

#include <fsm/core/headers/basic-types/Size+Index.hpp>                  // Size
#include <fsm/core/headers/misc/support-for-collections/FSM_ITS_RANGE.hpp>   // FSM_ITS_RANGE    
#include <fsm/core/headers/failure/detecting/hopefully.hpp>   // hopefully
#include <fsm/core/headers/failure/expressing/FSM_FAIL.hpp>    // FSM_FAIL_
#include <fsm/core/headers/constructs/declarations/type_builders.hpp>                // in_, array_of

#include <algorithm>
#include <iterator>
#include <set>
#include <stdexcept>

#include <stddef.h>         // size_t

namespace fabulous_support_machinery::_definitions {
    using   std::find,              // <algorithm>
            std::end,               // <iterator>
            std::set,               // <queue>
            std::out_of_range;      // <stdexcept>

    template< class Key, class Compare, class Allocator >
    auto contains( in_<Key> key, in_<set<Key, Compare, Allocator>> keys )
        -> bool
    { return keys.find( key ) != keys.end(); }

    template< class Item, Size array_size >
    constexpr auto contains( in_<Item> value, in_<array_of_<array_size, Item>> raw_array )
        -> bool
    { return (find( FSM_ITS_RANGE( raw_array ), value ) != end( raw_array )); }

    // TODO: other set operations.
    // TODO: also for unordered set.
    // TODO: also ditto for map.

    namespace d = _definitions;
    namespace exports { using
        d::contains;
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace _definitions::exports; }
