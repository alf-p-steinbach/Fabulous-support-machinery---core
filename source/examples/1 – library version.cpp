#include <fsm/core.hpp>
using namespace fsm;        // `output` and the rest.

auto main() -> int
{
    output( "The FSM (Fabulous Support Machinery) library.\n" );
    output( "Using {asd} with `format` from {}, in {}.\n",
        fsm_core_version,
        fmt_lib_source,     // Standard library or {fmt} library.
        cpp_version.to_string()
        );
}
