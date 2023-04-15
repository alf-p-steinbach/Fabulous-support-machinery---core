#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/support-for-collections/queue-utility.hpp>       // popped_front_of
#include <fsm/core/exports/support-for-collections/size-functions.hpp>      // int_size_of
#include <fsm/core/exports/constructs/type_builders.hpp>                    // in_, ref_
#include <fsm/core/exports/constructs/declarations/FSM_WITH.hpp>            // FSM_WITH
#include <fsm/core/exports/constructs/failure-handling/FSM_FAIL.hpp>        // FSM_FAIL
#include <fsm/core/exports/constructs/flow-control/repeat_times.hpp>               // repeat_times
#include <fsm/core/exports/meta-type/class-kinds/Movable.hpp>               // Movable
#include <fsm/core/exports/support-for-threading/Mutex_locker.hpp>          // Mutex_locker
#include <fsm/core/exports/support-for-time/Duration.hpp>                   // Duration

#include <condition_variable>
#include <mutex>
#include <queue>
#include <variant>

namespace fabulous_support_machinery::_definitions {
    using   std::condition_variable,            // <condition_variable>
            std::mutex, std::unique_lock,       // <mutex>
            std::queue,                         // <queue>
            std::get, std::variant;             // <variant>

    template< class Item >
    class Shared_queue_
    {
        queue<Item>     m_queue;
        
        mutable mutex                   m_mutex;
        mutable condition_variable      m_condition;
        
        auto length() const -> int      { return int_size_of( m_queue ); }
        auto is_empty() const -> bool   { return m_queue.empty(); }

    public:
        class Access:
            public Movable
        {
            friend class Shared_queue_;
            using Q_ptr = variant<Shared_queue_*, const Shared_queue_*>;

            Q_ptr               m_p_queue;
            Mutex_locker        m_mutex_locker;
            int                 m_n_notifications   = 0;
            
            Access( Shared_queue_& q ): m_p_queue( &q ), m_mutex_locker( q.m_mutex ) {}
            Access( const Shared_queue_& q ): m_p_queue( &q ), m_mutex_locker( q.m_mutex ) {}

            auto shared_queue() -> Shared_queue_& { return *get<Shared_queue_*>( m_p_queue ); }
    
            auto shared_queue() const
                -> const Shared_queue_&
            { return *(m_p_queue.index() == 0? get<0>( m_p_queue ) : get<1>( m_p_queue )); }
            
        public:
            ~Access()
            {
                m_mutex_locker.unlock();
                repeat_times( m_n_notifications, [&]{
                    shared_queue().m_condition.notify_one();
                } );
            }

            auto length() const -> int      { return shared_queue().length(); }
            auto is_empty() const -> bool   { return shared_queue().is_empty(); }
            
            void wait_for_items()
            {
                if( not is_empty() ) { return; }
                shared_queue().m_condition.wait(
                    m_mutex_locker,
                    [&]() -> bool { return not is_empty(); }
                    );
            }

            auto wait_for_items_for( const Duration duration )
                -> bool
            {
                if( not is_empty() ) { return true; }
                // TODO: handle possible overflow in `steady_clock::now() + duration`.
                const bool timed_out = not shared_queue().m_condition.wait_for(
                    m_mutex_locker, duration, [&]() -> bool { return not is_empty(); }
                    );
                return not timed_out;
            }

            void enq( Item item, const bool notify = true )
            {
                shared_queue().m_queue.push( move( item ) );
                m_n_notifications += notify;
            }

            auto deq() -> Item
            {
                wait_for_items();
                hopefully( not is_empty() )
                    or FSM_FAIL( "Waited for items but got none; shared_queue is empty." );
                return popped_front_of( shared_queue().m_queue );
            }
        };

        auto access() -> Access                 { return Access( *this ); }
        auto access() const -> const Access     { return Access( *this ); }
    };

    namespace d = _definitions;
    namespace exports { using
        d::Shared_queue_;
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace _definitions::exports; }
