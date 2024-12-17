#include <fsm/core/constructs/introspection/name_of_/raw_name_of_exactly_.hpp>
   //     fsm/core/constructs/introspection/name_of_/raw_name_of_exactly_.hpp
#include <iostream>
using   std::cout;

auto main() -> int
{
    const auto name = fsm::introspection::raw_name_of_exactly_<int>();
    cout << name << "\n";
}
