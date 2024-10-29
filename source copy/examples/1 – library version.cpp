#include <fsm/core.hpp>
using namespace fsm;        // `put` and the rest.

auto main() -> int
{
    put( "The FSM (Fabulous Support Machinery) library.\n" );
    put( "Using {} with `format` from {}, in {}.\n",
        fsm_core_version, fmt_lib_source, cpp_version.to_string()
        );
}
