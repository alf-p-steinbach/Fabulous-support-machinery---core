#include <fsm/core.hpp>
#include <iostream>

auto main() -> int
{
    using std::cout;
    cout << "Using " << fsm::core_version.description << ".\n";
    cout << "C++" << (FSM_CPP_VERSION / 100) % 100 << ".\n";
}
