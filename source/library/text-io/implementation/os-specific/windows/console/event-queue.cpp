// Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/text-io/implementation/os-specific/windows/console/_os/event-translation.hpp>
#include <fsm/text-io/exports/console/event-queue.hpp>

#include <fsm/core/exports/misc/support-for-collections/queue-utility.hpp>       // popped_front_of

namespace fabulous_support_machinery::console::_definitions {

    auto os::event_is_available()
        -> bool
    {
        _os::translate_available_api_events();
        return (not is_empty( _os::translated_events() ));
    }

    auto os::next_event()
        -> Event_holder
    {
        while( is_empty( _os::translated_events() ) ) {
            _os::translate_one_api_event();
        }
        return popped_front_of( _os::translated_events() );
    }
}  // namespace fabulous_support_machinery::console::_definitions
