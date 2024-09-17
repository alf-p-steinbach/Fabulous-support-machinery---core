#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
//
// There is unfortunately no known portable way to stop the compilation if this assert fires,
// and there is apparently no way to detect UTF-8 as execution character set in preprocessing.

namespace fsm {
    constexpr auto utf8_is_the_execution_character_set()
        -> bool
    {
        constexpr auto& slashed_o = "ø";
        return (sizeof( slashed_o ) == 3 and slashed_o[0] == '\xC3' and slashed_o[1] == '\xB8');
    }
}  // namespace fsm

static_assert(
    fsm::utf8_is_the_execution_character_set(),
    "The execution character set must be UTF-8, e.g. use MSVC option \"/utf-8\"."
    );
