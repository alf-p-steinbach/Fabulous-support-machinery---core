#include <fsm/core.hpp>
using   fsm::put, fsm::trimmed, fsm::input_line;    // Or just `using namespace fsm;`.

#include <string>
using   std::string;

auto main() -> int
{
    const string username = input_line( "Hi, what’s your name? " ); // Trimmed by default.
    put( "Pleased to meet you, {}!\n", username.empty()? "ℕ.ℕ." : username );
}
