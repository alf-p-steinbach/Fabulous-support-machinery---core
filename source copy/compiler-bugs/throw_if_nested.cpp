    #include <exception>
    #include <iostream>
    #include <stdexcept>
    using namespace std;

    #include <stdlib.h>         // exit, EXIT_...

    void throw_nested()
    {
        try {
            throw runtime_error( "First exception" );
        } catch( ... ) {
            throw_with_nested( runtime_error( "Second exception" ) );
        }
    }

    void check( const exception& x )
    {
        cout << "Checking...\n";
        try {
            //! rethrow_if_nested( x );     -- "libc++abi: terminating"
            if( const auto p_nest = dynamic_cast<const nested_exception*>( &x ) ) {
                cout << "Internal rethrowing...\n";
                //! p_nest->rethrow_nested();       -- "libc++abi: terminating"
                const auto x_ptr = p_nest->nested_ptr();
                if( not x_ptr ) {
                    cout << "!Nested exception pointer is null.\n";
                    exit( EXIT_FAILURE );           //! libc++
                }
                rethrow_exception( x_ptr );
            }
            cout << "Not nested.\n";
        } catch( ... ) {
            cout << "Nested!\n";
        }
        cout << "Done.\n";
    }

    auto main() -> int
    {
        try {
            throw_nested();
        } catch( const exception& x ) {
            check( x );
        }
    }
