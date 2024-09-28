#include <fsm/core.hpp>
using   fsm::put;

auto main() -> int
{
    put( "Using {}.\n", fsm::core_version.description );
    put( "C++ {}.\n", (FSM_CPP_VERSION / 100) % 100 );
}
