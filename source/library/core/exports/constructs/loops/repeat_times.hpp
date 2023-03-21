#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/type_builders.hpp>        // in_

namespace fabulous_support_machinery {
    
    template< class Func >
    void repeat_times( const int n, in_<Func> f )
    {
        for( int i = 1; i <= n; ++i ) { f(); }
    }

}  // namespace fabulous_support_machinery
