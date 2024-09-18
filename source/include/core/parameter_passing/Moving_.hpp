#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <utility>

namespace fsm_definitions {
    using   std::forward, std::move;        // <utility>

    namespace parameter_passing {
        template< class Type >
        class Moving_
        {
            Type    m_object;
            
        public:
            template< class Arg >
            Moving_( Arg&& arg ): m_object( forward<Arg>( arg ) ) {}
            
            Moving_( Moving_& other ): m_object( move( other.m_object ) ) {}
            Moving_( Moving_&& other ): m_object( move( other.m_object ) ) {}
            
            operator Type&& () noexcept { return move( m_object ); }

            operator Type () const = delete;
            operator const Type () const = delete;
        };
    }  // namespace parameter_passing
}  // namespace fsm_definitions

namespace fsm {
    inline namespace parameter_passing {
        using namespace fsm_definitions::parameter_passing;
    }
}  // namespace fsm
