#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <utility>

namespace fabulous_support_machinery {
    
    namespace boolean_ops {
        
        // AND
        template< class... Args >
        auto all_of( const Args&&... args ) -> bool { return (args and ...); }

        // OR
        template< class... Args >
        auto any_of( const Args&&... args ) -> bool { return (args or ...); }

        // XOR.
        template< class... Args >
        auto exactly_one_of( const Args&&... args ) -> bool { return ((!!args + ...) == 1); }
    }  // namespace boolean ops
    
    using namespace boolean_ops;
}  // namespace fabulous_support_machinery
