#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/text-io/exports/keyboard/continuous-effect-keys.hpp>      // Continuous_key_effect::Enum
#include <fsm/text-io/exports/keyboard/Key_code.hpp>                    // Key code names
#include <fsm/text-io/exports/keyboard/key-modifiers.hpp>               // Key_modifier, Key_modifier_set
#include <fsm/core/exports/text/encoding/u8/Code_point_.hpp>            // Code_point_
#include <fsm/core/exports/meta-type/class-kinds.hpp>                   // Polymorphic

#include <assert.h>     // assert

namespace fabulous_support_machinery::console::_definitions {

    //------------------------------------- Hierarchy:
    //  class Event;
    //      class Keyboard_event;
    //          class Keyboard_unicode_event;
    //          class Keyboard_continuous_effect_key_event;
    //          class Keyboard_special_key_event;
    //  class Mouse_event;



    class Event:
        public Polymorphic
    {
    protected:
        Event() {}
        
        // TODO: common timestamp?
    };
    

    class Keyboard_event:
        public Event
    {
    private:
        Key_code::Enum     m_key_code;         // A Windows virtual key code, e.g. VK_TAB.
        Key_modifier_set    m_modifiers;

    protected:
        Keyboard_event( const Key_code::Enum code, const Key_modifier_set modifiers = {} ):
            m_modifiers( modifiers )
        {}
        
    public:
        auto key_code() const   -> Key_code::Enum      { return m_key_code; }
        auto modifiers() const  -> Key_modifier_set     { return m_modifiers; }
    };


    // Unicode code points, not /characters/ like the double code-point flags, but:
    class Keyboard_unicode_event:
        public Keyboard_event
    {
        u8::Code_point  m_code_point;

    public:
        Keyboard_unicode_event(
            const Key_code::Enum       code,
            const u8::Code_point        value,
            const Key_modifier_set      modifiers = {}
            ):
            Keyboard_event( code, modifiers ),
            m_code_point( value )
        {}

        auto unicode() const -> const u8::Code_point& { return m_code_point; }
    };


    class Keyboard_continuous_effect_key_event:
        public Keyboard_event
    {
    public:
        Keyboard_continuous_effect_key_event(
            const Continuous_key_effect::Enum   effect,
            const Key_modifier_set              modifiers = {}
            ):
            Keyboard_event( as_key_code( effect ), modifiers )
        {}
        // start, stop
    };


    // Function keys, escape, etc.:
    class Keyboard_special_key_event:
        public Keyboard_event
    {
    public:
        Keyboard_special_key_event( const Key_code::Enum code ): Keyboard_event( code ) {}     // TODO
    };


    class Mouse_event:
        public Event
    {
    protected:
        Mouse_event() {}
    };


    namespace d = _definitions;
    namespace exports{ using
        d::Event,
        d::Keyboard_event,
        d::Keyboard_unicode_event,
        d::Keyboard_continuous_effect_key_event,
        d::Keyboard_special_key_event,
        d::Mouse_event;
    }  // namespace exports
}  // namespace fabulous_support_machinery::console::_definitions

namespace fabulous_support_machinery::console   { using namespace _definitions::exports; }
