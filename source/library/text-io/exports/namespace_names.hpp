﻿#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/declarations/FSM_NS_FROM.hpp>     // FSM_NS_FROM

namespace fabulous_support_machinery{
    namespace console{}  namespace std_streams{}  namespace fmtlib{}

    namespace namespace_names {
        namespace fsm = fabulous_support_machinery;
        FSM_NS_FROM( fsm, console );
        FSM_NS_FROM( fsm, std_streams );
        FSM_NS_FROM( fsm, fmtlib );
    }
}  // namespace fabulous_support_machinery::namespace_names