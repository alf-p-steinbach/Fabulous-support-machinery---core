#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/misc/support-for-collections/set-utility.hpp>     // contains
#include <fsm/text-io/exports/keyboard/Key_code.hpp>                    // Key_code

namespace fabulous_support_machinery {
    // Continuous effect while pressed: Backspace, Delete, PgUp, PgDn, Left, Up, Down, Right.
    struct Continuous_key_effect{
        enum Enum: int {
            delete_left     = Key_code::back_key,
            delete_right    = Key_code::delete_key,
            page_up         = Key_code::page_up_key,
            page_down       = Key_code::page_down_key,
            cursor_left     = Key_code::left_key,
            cursor_up       = Key_code::up_key,
            cursor_down     = Key_code::down_key,
            cursor_right    = Key_code::right_key
        };

        static inline constexpr Key_code::Enum keys[] =
        {
            Key_code::back_key,
            Key_code::delete_key,
            Key_code::page_up_key,
            Key_code::page_down_key,
            Key_code::left_key,
            Key_code::up_key,
            Key_code::down_key,
            Key_code::right_key
        };
    };

    constexpr auto as_key_code( const Continuous_key_effect::Enum effect )
        -> Key_code::Enum
    { return static_cast<Key_code::Enum>( effect ); }

    constexpr auto is_continuous_effect_key( const Key_code::Enum key )
        -> bool
    { return contains( key, Continuous_key_effect::keys ); }

}  // namespace fabulous_support_machinery
