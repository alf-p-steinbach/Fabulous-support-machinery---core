#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/_all.hpp>
#include <fsm/$-macros.hpp>

namespace fsm = fabulous_support_machinery;

namespace fabulous_support_machinery::namespace_names {
    $nsname_from( fsm, console );  $nsname_from( fsm, std_streams );  $nsname_from( fsm, fmtlib );
    $nsname_from( fsm, u8 );  $nsname_from( fsm, unicode );
    $nsname_from( fsm, iterable_for );
    $nsname_from( fsm, stack_ops );
}  // namespace fabulous_support_machinery::namespace_names
