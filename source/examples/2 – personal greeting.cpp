#include <fsm/core.hpp>
using   fsm::is_empty, fsm::input, fsm::output;

#include <string>
using   std::string;

auto main() -> int
{
    const string username = input( "Hi, what’s your name? " );  // Trimmed by default.
    output( "Pleased to meet you, {}!\n", is_empty( username )? "ℕ.ℕ." : username );
}
