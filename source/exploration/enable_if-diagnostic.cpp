#include <fsm/_simple.hpp>

#include <type_traits>
#include <utility>

template< class T, FSM_ENABLE_IF( true and std::is_array_v<T> ) >
auto foo( T* ) -> void {}

// template< class T >
// void foo( T ) {}

auto main() -> int
{
    int x;
    foo( &x );
}
