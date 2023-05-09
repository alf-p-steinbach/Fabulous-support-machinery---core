﻿#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/declarations/FSM_NSNAME_FROM.hpp>     // FSM_NSNAME_FROM

namespace fabulous_support_machinery{
    namespace console{}  namespace std_streams{}  namespace fmtlib{}
    namespace u8{}  namespace unicode{}
    namespace stack_ops{}
    namespace queue_ops{}

    namespace namespace_names {
        namespace fsm = fabulous_support_machinery;
        FSM_NSNAME_FROM( fsm, console );
        FSM_NSNAME_FROM( fsm, std_streams );
        FSM_NSNAME_FROM( fsm, fmtlib );
        
        FSM_NSNAME_FROM( fsm, u8 );
        FSM_NSNAME_FROM( fsm, unicode );
        
        FSM_NSNAME_FROM( fsm, stack_ops );
        FSM_NSNAME_FROM( fsm, queue_ops );
    }
}  // namespace fabulous_support_machinery::namespace_names
