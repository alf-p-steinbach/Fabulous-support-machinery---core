#include <iostream>

auto main() -> int
{
    const int& x = 42;
    decltype((x))* p = 0;
    
}