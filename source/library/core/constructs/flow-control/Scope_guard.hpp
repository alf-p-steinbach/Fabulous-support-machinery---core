#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/meta-type/class-kinds/Only_movable.hpp>      // Only_movable

#include    <functional>

namespace fsm_definitions {
    namespace fsm = fabulous_support_machinery;

    using   fsm::Only_movable;
    using   std::function;
    
    class Scope_guard:
        public Only_movable
    {
        function<void()>    m_cleanup;
        
    public:
        ~Scope_guard() { m_cleanup(); }

        Scope_guard( function<void()> cleanup ):
            m_cleanup( move( cleanup ) )
        {}
        
        void dismiss() { m_cleanup = []{}; }
    };

    namespace d = fsm_definitions;
    namespace exports{ using
        d::Scope_guard;
    }  // namespace exports
}  // namespace fsm_definitions

namespace fabulous_support_machinery    { using namespace fsm_definitions::exports; }
