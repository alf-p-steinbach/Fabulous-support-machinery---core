#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/declarations/FSM_ENABLE_IF_.hpp>                  // FSM_ENABLE_IF_
#include <fsm/core/exports/io/keyboard/key_codes.hpp>                                   // Key code names.
#include <fsm/core/exports/text/encoding/u8/Code_point_.hpp>                            // Code_point_
#include <fsm/core/exports/meta-type/type-inspectors/compile-time-type-inspectors.hpp>  // are_derived_and_base_, Bare_
#include <fsm/core/exports/meta-type/Typelist_.hpp>                                     // Typelist_

#include <variant>

#include <assert.h>     // assert

namespace fabulous_support_machinery::console::_definitions {
    using   std::get_if, std::variant, std::visit, std::holds_alternative;  // <variant>

    //------------------------------------- Hierarchy:
    class Event;
        class Keyboard_event;
            class Keyboard_character_event;
            class Keyboard_modal_action_event;
        class Mouse_event;
    class Event_holder;


    //-------------------------------------:
    
    class Event
    {
        auto operator=( in_<Event> ) -> Event& = delete;

    protected:
        inline virtual ~Event() = 0;
        
        // TODO: common timestamp?
    };
    
    inline Event::~Event() {}
    
    class Keyboard_event:
        public Event
    {
    protected:
        inline virtual ~Keyboard_event() = 0;
    };

    inline Keyboard_event::~Keyboard_event() {}

    // Unicode code points, not /characters/ like the double code-point flags, but:
    class Keyboard_character_event:
        public Keyboard_event
    {
    public:
        const u8::Code_point    code_point;
        
        Keyboard_character_event( const u8::Code_point value ): code_point( value ) {}
    };

    // "is pressed" continuous effect Backspace, Delete, PgUp, PgDn, left, up, down, right:
    class Keyboard_modal_action_event:
        public Keyboard_event
    {
        // start, stop
    };

    // Function keys, escape, etc.:
    class Keyboard_keypress_event:
        public Keyboard_event
    {};

    class Mouse_event:
        public Event
    {
    protected:
        inline virtual ~Mouse_event() = 0;
    };

    inline Mouse_event::~Mouse_event() {}

    class Event_holder
    {
        using Type_list = Typelist_<
            Keyboard_character_event,
            Keyboard_modal_action_event,
            Keyboard_keypress_event
            // Mouse_event
            >;
        using Variant = Type_list::Specialization_of_<variant>;
            
        Variant m_variant;

    public:
        template< class Type,
            FSM_ENABLE_IF_( are_derived_and_base_<Type, Event> )
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
                    return are_derived_and_base_< Bare_<decltype( e )>, Type >;
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

    extern auto event_is_available() -> bool;
    extern auto next_event() -> Event_holder;

    namespace d = _definitions;
    namespace exports{ using
        d::Event,
        d::Keyboard_event,
        d::Keyboard_keypress_event,
        d::Keyboard_modal_action_event,
        d::Mouse_event,
        d::Event_holder,
        d::event_is_available, d::next_event;
    }  // namespace exports
}  // namespace fabulous_support_machinery::console::_definitions

namespace fabulous_support_machinery::console   { using namespace _definitions::exports; }
