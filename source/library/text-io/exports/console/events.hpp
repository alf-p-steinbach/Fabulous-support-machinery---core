#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/declarations/FSM_ENABLE_IF.hpp>   // FSM_ENABLE_IF
#include <fsm/core/exports/constructs/declarations/enum-support.hpp>    // n_enumerators_of_
#include <fsm/text-io/exports/keyboard/key_codes.hpp>                   // Key code names.
#include <fsm/core/exports/text/encoding/u8/Code_point_.hpp>            // Code_point_
#include <fsm/core/exports/meta-type/class-kinds.hpp>                   // Movable, Non_instantiable, Polymorphic
#include <fsm/core/exports/meta-type/type-inspectors.hpp>               // are_derived_and_base_, Bare_
#include <fsm/core/exports/meta-type/Typelist_.hpp>                     // Typelist_

#include <initializer_list>
#include <variant>

#include <assert.h>     // assert

namespace fabulous_support_machinery::console::_definitions {
    using   std::initializer_list,                                          // <initializer_list>
            std::get_if, std::variant, std::visit, std::holds_alternative;  // <variant>

    //------------------------------------- Hierarchy:
    class Event;
        class Keyboard_event;
            class Keyboard_character_event;
            class Keyboard_modal_action_event;
        class Mouse_event;

    class Event_holder;


    //-------------------------------------:
    
    class Event:
        // public Movable,      // ???
        public Polymorphic
    {
    protected:
        Event() {}
        
        // TODO: common timestamp?
    };
    
    // The name “os” refers to “Windows key” in Windows and “Command key” on a Mac.
    struct Key_modifier: Non_instantiable { enum Enum: int { os, alt, ctrl, shift, _ }; };
    
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
    
    class Keyboard_event:
        public Event
    {
    public:

    private:
        Key_modifier_set    m_modifiers;

    protected:
        Keyboard_event( const Key_modifier_set modifiers = {} ) : m_modifiers( modifiers ) {}
    };

    // Unicode code points, not /characters/ like the double code-point flags, but:
    class Keyboard_unicode_event:
        public Keyboard_event
    {
        u8::Code_point  m_code_point;

    public:
        Keyboard_unicode_event( const u8::Code_point value ): m_code_point( value ) {}
        auto code_point() const -> const u8::Code_point& { return m_code_point; }
    };

    // "is pressed" continuous effect Backspace, Delete, PgUp, PgDn, left, up, down, right:
    class Keyboard_modal_action_event:
        public Keyboard_event
    {
        // TODO enum{ released, pressed }
        // start, stop
    };

    // Function keys, escape, etc.:
    class Keyboard_special_key_event:
        public Keyboard_event
    {
        int     m_key_code;         // A Windows virtual key code, e.g. VK_TAB.
        
    public:
        Keyboard_special_key_event( const int code ): m_key_code( code ) {}
    };

    class Mouse_event:
        public Event
    {
    protected:
        Mouse_event() {}
    };

    class Event_holder
    {
        using Type_list = Typelist_<
            Keyboard_unicode_event,
            Keyboard_modal_action_event,
            Keyboard_special_key_event
            // Mouse_event
            >;
        using Variant = Type_list::Specialization_of_<variant>;
            
        Variant m_variant;

    public:
        template< class Type,
            FSM_ENABLE_IF( are_derived_and_base_<Type, Event> )
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

    namespace os {
        extern auto event_is_available() -> bool;
        extern auto next_event() -> Event_holder;
    }  // namespace os
    
    using   os::event_is_available,
            os::next_event;

    namespace d = _definitions;
    namespace exports{ using
        d::Event,
        d::Keyboard_event,
        d::Keyboard_unicode_event,
        d::Keyboard_modal_action_event,
        d::Keyboard_special_key_event,
        d::Mouse_event,
        d::Event_holder,
        d::event_is_available, d::next_event;
    }  // namespace exports
}  // namespace fabulous_support_machinery::console::_definitions

namespace fabulous_support_machinery::console   { using namespace _definitions::exports; }
