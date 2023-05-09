#include <fsm/_simple.hpp>
using namespace fsm::namespace_names;       // stack_ops, console

#include <stack>
using   std::stack;

auto main() -> int
{
    #if defined TEST_CONST
        const auto st = fsm::make_stack<int>( 1, 2, 3, 4, 5 );
    #elif defined TEST_VAR
        stack<int> st;
        for( const int v: {1, 2, 3, 4, 5} ) { st.push( v ); }
    #else
        #error "Define TEST_CONST or TEST_VAR."
        #include <stop-compilation>
    #endif

    using fsm::container_for;
    for( const int v: container_for( st ) ) { console::output( v, "\n" ); }
}
