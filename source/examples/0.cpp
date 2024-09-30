#include <fsm/core.hpp>
using   fsm::put;

auto main() -> int
{
    put( "The FSM (Fabulous Support Machinery) library.\n" );
    put( "Using {} with `format` from {}, in {}.\n",
        fsm::fsm_core_version, fsm::fmt_lib_source, fsm::cpp_version.to_string()
        );
}
