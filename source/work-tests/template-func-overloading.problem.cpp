#include <stack>
#include <type_traits>
#include <utility>
#include <vector>
using   std::stack,
        std::remove_reference_t, std::remove_const_t,
        std::forward,
        std::vector;

template< class T > using in_ = const T&;

template< class Collection >
constexpr auto all_of( Collection&& )
    -> int
{ return 100; }

template< class Item, class Container >
auto all_of( in_<stack<Item, Container>> )
    -> int
{ return 101; }

#include <stdio.h>
auto main() -> int
{
    stack<int> st;
    printf( "%d\n", all_of( st ) );         // 100 but want 101 - overload for stack
    vector<int> v;
    printf( "%d\n", all_of( v ) );          // 100 - general case
}
