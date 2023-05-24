#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/headers/+std-cpp-language.hpp>

#include <fsm/core/headers/constructs/declarations/enum-support.hpp>        // n_enumerators_of_
#include <fsm/core/headers/constructs/declarations/type_builders.hpp>       // ref_

namespace fabulous_support_machinery {

    // The name “os” refers to “Windows key” in Windows and “Command key” on a Mac.
    struct Key_modifier: Non_instantiable { enum Enum: int {
        os, alt, ctrl, shift, _
    }; };
    
    class Key_modifier_set
    {
        enum{ n_bits = n_enumerators_of_<Key_modifier> };
        unsigned    m_bits  = 0;
        
        constexpr Key_modifier_set( const unsigned bits ): m_bits( bits ) {}

    public:
        constexpr Key_modifier_set() {}
        
        constexpr Key_modifier_set( const Key_modifier::Enum e ): m_bits( 1u << e ) {}
        
        friend
        constexpr auto operator|( const Key_modifier_set a, const Key_modifier_set b )
            -> Key_modifier_set
        { return {a.m_bits | b.m_bits}; }
        
        friend
        constexpr auto contains( const Key_modifier_set set, const Key_modifier::Enum e )
            -> bool
        { return !!(set.m_bits & (1u << e)); }
    };

    inline auto operator|=( ref_<Key_modifier_set> lhs, const Key_modifier_set rhs )
        -> ref_<Key_modifier_set>
    {
        lhs = (lhs | rhs);
        return lhs;
    }
}  // namespace fabulous_support_machinery
