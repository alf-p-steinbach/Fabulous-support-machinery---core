﻿#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/failure/detecting/hopefully.hpp>                     // hopefully
#include <fsm/core/types/fundamental/Size+Index.hpp>                    // Size
#include <fsm/core/constructs/declarations/type_builders.hpp>           // in_, array_of_
#include <fsm/core/misc/support-for-collections/FSM_ITS_RANGE.hpp>      // FSM_ITS_RANGE    

#include <algorithm>
#include <iterator>
#include <set>
#include <stdexcept>

#include <stddef.h>         // size_t

namespace fsm_definitions {
    namespace fsm = fabulous_support_machinery;
    using   fsm::Size,
            fsm::in_, fsm::array_of_,
            fsm::hopefully;
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

    namespace d = fsm_definitions;
    namespace exports { using
        d::contains;
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace fsm_definitions::exports; }
