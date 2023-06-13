#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

// #include <fsm/core/constructs/declarations/type_builders.hpp> // in_value_

#include <atomic>
#include <exception>
#include <thread>
#include <utility>

namespace fsm_definitions {
    using   std::atomic,
            std::current_exception, std::exception_ptr,
            std::thread,
            std::move;

    class Joining_thread_state
    {
    protected:
        atomic<bool>        m_has_termination_exception = false;
        exception_ptr       m_termination_exception;
    };

    class Joining_thread:
        private Joining_thread_state, // First base class, so is initialized first.
        public thread
    {
        using Base = thread;

    public:
        ~Joining_thread() { if( joinable() ) { join(); } }

        template< class Func, class... Args >
        Joining_thread( Func f_arg, Args&&... args ):
            Joining_thread_state(),
            thread( [this, f = move( f_arg ), args...]  // Capturing by reference would yield dangling arg-refs.
            {
                try {
                    f( args... );
                } catch( ... ) {
                    m_termination_exception = current_exception();
                    m_has_termination_exception = true;
                }
            } )
        {}

        auto has_exception() const -> bool { return m_has_termination_exception; }

        void rethrow_if_exception() const
        {
            if( m_has_termination_exception ) {
                rethrow_exception( m_termination_exception );
            }
        }
    };

    namespace d = fsm_definitions;
    namespace exports { using
        d::Joining_thread;
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery { using namespace fsm_definitions::exports; }
