#include <iomanip>
#include <iostream>
#include <string>
#include <stddef.h>
using namespace std;

using Index = ptrdiff_t;

auto main() -> int
{
    string line;
    while( getline( cin, line ) ) {
        const auto i_eq = static_cast<Index>( line.find( '=' ) );
        if( i_eq >= 0 ) {
            const string s1 = line.substr( 0, i_eq );
            const string s2 = line.substr( i_eq + 1 );
            cout << setw( 28 ) << left << s1;
            cout << "= ";
            cout << s2 << endl;
        } else {
            cout << line << endl;
        }
    }
}
