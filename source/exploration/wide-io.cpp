#include <iterator>
#include <locale.h>
#include <wchar.h>

template< class T > using in_ = const T&;
template< class T > auto int_size( in_<T> o ) -> int { return int( std::size( o ) ); }

auto main() -> int
{
    setlocale( LC_ALL, "en_US.utf8" );
    const auto loc = setlocale( 0, nullptr );
    puts( loc );
    fputws( L"Every 日本国 кошка loves blåbærsyltetøy!", stdout );
    fputws( L"Name please? ", stdout );
    wchar_t name[80];
    fgetws( name, int_size( name ), stdin );
    fwprintf( stdout, L"Pleased to meet you, %ls. Goodbye!\n", name );
}
