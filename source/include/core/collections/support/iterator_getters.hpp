#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <iterator>         // std::(begin, end)

namespace fsm_definitions {
    namespace collections{ inline namespace iterator_getters {

        template< class Collection >
        auto begin_of( Collection& c )
            -> auto
        { using std::begin; return begin( c ); }

        template< class Collection > auto begin_of( Collection&& ) -> auto = delete;

        template< class Collection >
        auto end_of( Collection& c )
            -> auto
        { using std::end; return end( c ); }

        template< class Collection > auto end_of( Collection&& ) -> auto = delete;

    } }  // namespace collections / inline namespace iterator_getters
}  // namespace fsm_definitions

namespace fsm {
    inline namespace collections { using namespace fsm_definitions::collections; }
}  // namespace fsm
