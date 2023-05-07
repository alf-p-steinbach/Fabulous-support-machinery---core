#include <fsm/_simple.hpp>
#include <stack>
using   std::stack;

auto main() -> int
{
    stack<int> st;
    for( const int v: {1, 2, 3, 4, 5} ) { st.push( v ); }

    using namespace fsm::stack_ops;
    for( const int v: all_of( st ) ) { console::output( v, "\n" ); }
}
