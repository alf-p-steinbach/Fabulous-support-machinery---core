#include <fsm/core.hpp>
namespace fsm = fabulous_support_machinery;
using   fsm::in_, fsm::hopefully;

#include <winapi-header-wrappers/windows-h.for-utf-16.hpp>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
using namespace std::literals;
namespace this_thread = std::this_thread;
using   std::cin, std::cout, std::endl,
        std::string;

#include <assert.h>

auto main() -> int
{
    namespace event = fsm::console::event;
    using Char_event = event::keyboard::Character;
    for( ;; ) {
        const event::Holder ev = event::next();
        if( ev.holds<Char_event>() ) {
            const fsm::u8::Code_point& code = ev.ref<Char_event>().code_point;
            if( code.codepoint() == 27 ) {
                break;
            }
            cout << "Char event, code = " << code.codepoint() << endl;
        } else {
            cout << "Some event." << endl;
        }
    }
}
