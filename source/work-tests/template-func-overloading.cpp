#include <stack>
#include <type_traits>
#include <utility>
#include <vector>
using   std::stack,
        std::remove_reference_t, std::remove_const_t,
        std::forward,
        std::vector;

template< class T > using in_ = const T&;

template< class Collection > struct Iterable_for_;

template< class Collection >
constexpr auto all_of( Collection&& c )
    -> int
{
    using C = remove_const_t<remove_reference_t<Collection>>;
    return Iterable_for_<C>::all_of( forward<Collection>( c ) );
}

template< class Collection >
struct Iterable_for_
{
    template< class Collection_arg >
    static constexpr auto all_of( Collection_arg&& )
        -> int
    { return 100; }
};

template< class Item, class Container >
struct Iterable_for_<stack<Item, Container>>
{
    static auto all_of( in_<stack<Item, Container>> )
        -> int
    { return 101; }
};

#include <stdio.h>
auto main() -> int
{
    stack<int> st;
    printf( "%d\n", all_of( st ) );         // 101 - specialization for stack
    vector<int> v;
    printf( "%d\n", all_of( v ) );          // 100 - general case
}
