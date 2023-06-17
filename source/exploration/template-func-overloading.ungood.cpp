#include <stack>
#include <type_traits>
#include <utility>
#include <vector>
using   std::stack,
        std::remove_reference_t, std::remove_const_t,
        std::forward, std::as_const,
        std::vector;

template< class T > using in_ = const T&;

// template< class Type >
// struct Type_carrier_ { using T = Type; };

// struct Not_best_match{ Not_best_match( ... ) {} };

// template< class Collection >
// constexpr auto all_of( Collection&& c )
    // -> int
// {
    // using C = remove_const_t<remove_reference_t<Collection>>;
    // return all_of( forward<Collection>( c ), Type_carrier_<C>() );
// }

template< class Item, class Container >
auto all_of( in_<stack<Item, Container>> ) //, Type_carrier_<stack<Item, Container>> )
    -> int
{ return 101; }

template< class Item, class Container >
auto all_of( stack<Item, Container>& st ) //, Type_carrier_<stack<Item, Container>> tc )
    -> int
{ return all_of( as_const( st ) ); }

template< class Collection >
constexpr auto all_of( Collection&& ) //, Not_best_match )
    -> int
{ return 100; }

#include <stdio.h>
auto main() -> int
{
    stack<int> st;
    printf( "%d\n", all_of( st ) );         // MSVC 100 but want 101 - specialization for stack
    vector<int> v;
    printf( "%d\n", all_of( v ) );          // 100 - general case
}
