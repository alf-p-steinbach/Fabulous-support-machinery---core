#include <fsm/core/headers/meta-type/Typelist_.hpp>
namespace fsm = fabulous_support_machinery;
using   fsm::Typelist_, fsm::Joined_;

#include <stdio.h>

auto english( const bool v ) -> const char* { return (v? "true" : "false"); }

auto main() -> int
{
    using A = Typelist_<>;
    printf( "A has %d types.\n", A::count );
    printf( "A contains `char` is %s.\n", english( A::contains_<char> ) );
    printf( "A contains `int` is %s.\n", english( A::contains_<int> ) );
    printf( "A contains `double` is %s.\n", english( A::contains_<double> ) );
    printf( "\n" );

    using B = Typelist_<double>;
    printf( "B has %d types.\n", B::count );
    printf( "B contains `char` is %s.\n", english( B::contains_<char> ) );
    printf( "B contains `int` is %s.\n", english( B::contains_<int> ) );
    printf( "B contains `double` is %s.\n", english( B::contains_<double> ) );
    printf( "\n" );

    using C = Typelist_<char, double>;
    printf( "C has %d types.\n", C::count );
    printf( "C contains `char` is %s.\n", english( C::contains_<char> ) );
    printf( "C contains `int` is %s.\n", english( C::contains_<int> ) );
    printf( "C contains `double` is %s.\n", english( C::contains_<double> ) );
    printf( "\n" );

    using All = Joined_<B, C, Typelist_<int>>;
    printf( "All has %d types.\n", All::count );
    printf( "All contains `char` is %s.\n", english( All::contains_<char> ) );
    printf( "All contains `int` is %s.\n", english( All::contains_<int> ) );
    printf( "All contains `double` is %s.\n", english( All::contains_<double> ) );
    printf( "\n" );
}
