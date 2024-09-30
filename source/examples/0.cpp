#include <fsm/core.hpp>
using   fsm::put;

auto main() -> int
{
    put( "The FSM (Fabulous Support Machinery) library.\n" );
    put( "Using {} in {}.\n", fsm::fsm_core_version, fsm::cpp_version.to_string() );
}
