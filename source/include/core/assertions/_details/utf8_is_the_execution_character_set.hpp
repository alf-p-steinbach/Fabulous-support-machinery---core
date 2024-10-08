﻿#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

namespace fsm {
    constexpr auto utf8_is_the_execution_character_set()
        -> bool
    {
        constexpr auto& slashed_o = "ø";
        return (sizeof( slashed_o ) == 3 and slashed_o[0] == '\xC3' and slashed_o[1] == '\xB8');
    }
}  // namespace fsm
