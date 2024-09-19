#include <fsm/core.hpp>
using   fsm::enabled_if_;

template< class T, bool = enabled_if_<T( 0.5 ) == 0.5>() >
void foo( T ) {}

auto main() -> int
{
    foo( 3.14 );            // OK.
    foo( 666 );             // !Nah. Should fail to compile.
}
