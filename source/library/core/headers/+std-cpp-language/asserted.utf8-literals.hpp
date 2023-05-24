#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include "utf8_is_the_execution_character_set.hpp"

// There is unfortunately no known portable way to stop the compilation if this assert fires,
// and there is apparently no way to detect UTF-8 as execution character set in preprocessing.
static_assert(
    fabulous_support_machinery::utf8_is_the_execution_character_set(),
    "The execution character set must be UTF-8 (e.g. MSVC option \"/utf-8\")."
    );
