#include <fsm/core.hpp>
using   fsm::put, fsm::trimmed, fsm::input_line;

#include <string>
using   std::string;

auto main() -> int
{
    const string username = trimmed( input_line( "Hi, what’s your name? " ) );
    put( "Pleased to meet you, {}!\n", username.empty()? "NN" : username );
}
