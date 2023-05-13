#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/meta-type/Typelist_.hpp>                     // Typelist_
#include <fsm/core/exports/meta-type/type-inspectors.hpp>               // are_base_and_derived_, Bare_
#include <fsm/text-io/exports/console/event-classes.hpp>

#include <initializer_list>
#include <variant>

#include <assert.h>     // assert

namespace fabulous_support_machinery::console::_definitions {
    using   std::initializer_list,                                          // <initializer_list>
            std::get_if, std::variant, std::visit, std::holds_alternative;  // <variant>

    //------------------------------------- Hierarchy:
    //  class Event;
    //      class Keyboard_event;
    //          class Keyboard_unicode_event;
    //          class Keyboard_continuous_effect_key_event;
    //          class Keyboard_special_key_event;
    //  class Mouse_event;

    class Event_holder
    {
        using Type_list = Typelist_<
            Keyboard_unicode_event,
            Keyboard_continuous_effect_key_event,
            Keyboard_special_key_event
            // Mouse_event
            >;
        using Variant = Type_list::Specialization_of_<variant>;
            
        Variant m_variant;

    public:
        template< class Type,
            FSM_ENABLE_IF( are_base_and_derived_<Event, Type> )
            >
        Event_holder( in_<Type> e ): m_variant( e ) {}
        
        template< class Type >
        auto variant_is_a() const
            -> bool
        {
            if( m_variant.index() == Type_list::index_of_<Type> ) {
                return true;
            } else {
                const auto is_specified_type = []( const auto& e )
                    -> bool
                {
                    return are_base_and_derived_<Type, Bare_<decltype( e )>>;
                };
                return visit( is_specified_type, m_variant );
            }
        }

        template< class Type >
        auto variant_as() const
            -> const Type&
        {
            if constexpr( Type_list::contains_<Type> ) {
                if( const Type* p = get_if<Type>( m_variant ) ) {
                    return *p;
                }
            }

            const auto get_p_event = []( const auto& e )
                -> const Type*
            {
                const auto result = dynamic_cast<const Type*>( &e );
                assert( result or !"Retrieval type is not base of or same as variant." );
                return result;
            };
            return *visit( get_p_event, m_variant );
        }

        auto variant_as_base() const -> const Event& { return variant_as<Event>(); }
    };

    namespace os {
        extern auto event_is_available() -> bool;
        extern auto next_event() -> Event_holder;
    }  // namespace os
    
    using   os::event_is_available,
            os::next_event;

    namespace d = _definitions;
    namespace exports{ using
        d::Event_holder,
        d::event_is_available, d::next_event;
    }  // namespace exports
}  // namespace fabulous_support_machinery::console::_definitions

namespace fabulous_support_machinery::console   { using namespace _definitions::exports; }
