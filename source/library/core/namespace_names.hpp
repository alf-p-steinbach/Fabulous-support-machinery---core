#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/constructs/declarations/FSM_NS_FROM.hpp>     // FSM_NS_FROM

namespace fabulous_support_machinery{
    namespace console{}  namespace std_streams{}  namespace fmtlib{}

    namespace boolean_ops{}     // core/constructs/expressions/boolean-operations.hpp
    namespace number_ops{}      // core/constructs/expressions/number-operations.hpp

    namespace u8{}              // core/text/encoding/u8.hpp
    namespace unicode{}         // core/text/encoding/unicode.hpp

    namespace its_range{}       // core/misc/support-for-collections/Iterator_pair_.hpp
    namespace queue_ops{}       // core/misc/support-for-collections/queue-utility.hpp
    namespace stack_ops{}       // core/misc/support-for-collections/stack-utility.hpp

    namespace namespace_names {
        namespace fsm = fabulous_support_machinery;
        FSM_NS_FROM( fsm, console );
        FSM_NS_FROM( fsm, std_streams );
        FSM_NS_FROM( fsm, fmtlib );

        FSM_NS_FROM( fsm, boolean_ops );

        FSM_NS_FROM( fsm, u8 );
        FSM_NS_FROM( fsm, unicode );

        FSM_NS_FROM( fsm, its_range );
        FSM_NS_FROM( fsm, queue_ops );
        FSM_NS_FROM( fsm, stack_ops );
    }
}  // namespace fabulous_support_machinery::namespace_names
