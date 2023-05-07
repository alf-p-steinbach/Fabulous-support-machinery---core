#include <fsm/_simple.hpp>
#include <stack>
using   std::stack;

auto main() -> int
{
    const auto st = fsm::make_stack<int>( 1, 2, 3, 4, 5 );
    // for( const int v: {1, 2, 3, 4, 5} ) { st.push( v ); }

    using namespace fsm::stack_ops;
    for( const int v: all_of( st ) ) { console::output( v, "\n" ); }
}
