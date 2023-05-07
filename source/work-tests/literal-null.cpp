#include <fsm/core/exports/misc/Literal_null.hpp>
namespace fsm = fabulous_support_machinery;

void foo( fsm::Literal_null ) {}

auto main() -> int
{
    foo( 0 );
    #ifdef FAIL_A
        foo( 1 - 1 );
    #endif
    #ifdef FAIL_B
        foo( nullptr );
    #endif
}
