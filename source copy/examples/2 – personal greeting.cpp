#include <fsm/core.hpp>
using   fsm::is_empty, fsm::input_line, fsm::put;   // Or just `using namespace fsm;`.

#include <string>
using   std::string;

auto main() -> int
{
    const string username = input_line( "Hi, what’s your name? " ); // Trimmed by default.
    put( "Pleased to meet you, {}!\n", is_empty( username )? "ℕ.ℕ." : username );
}
