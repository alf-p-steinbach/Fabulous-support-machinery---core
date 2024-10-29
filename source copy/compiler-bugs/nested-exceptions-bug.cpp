#include <exception>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>

#include <stdlib.h>         // EXIT_...

namespace machinery {
    using   std::current_exception, std::exception_ptr,                                 // <exception>
            std::rethrow_exception, std::rethrow_if_nested, std::throw_with_nested,     //     -"-
            std::function,                          // <functional>
            std::exception, std::runtime_error,     // <stdexcept>
            std::string;                            // <string>

    template< class Type > using in_ = const Type&;

    [[noreturn]] inline auto fail( in_<string> s )
        -> bool
    {
        const bool has_current_exception = !!current_exception();
        if( has_current_exception ) {
            throw_with_nested( runtime_error( s ) );
        } else {
            throw runtime_error( s );
        }
        for( ;; ) {}        // Should never get here.
    }

    class Unknown_exception:
        public exception
    {
        exception_ptr   m_ptr;

    public:
        Unknown_exception( in_<exception_ptr> p ): m_ptr( p ) {}
        auto ptr() const -> exception_ptr { return m_ptr; }
        auto what() const noexcept -> const char* override { return "<unknown exception>"; }
    };

    namespace recursive {
        inline auto for_each_nested_exception_in(
            in_<exception>                          x,
            in_<function<void( in_<exception> )>>   f
            ) -> bool
        {
            for( ;; ) {
                try {
                    rethrow_if_nested( x );     // Rethrows a nested exception, if any.
                    return true;
                } catch( in_<exception> nested_x ) {
                    f( nested_x );
                    return for_each_nested_exception_in( nested_x, f );
                } catch( ... ) {
                    f( Unknown_exception{ current_exception() } );
                    return false;
                }
            }
        }

        inline auto for_each_exception_in(
            in_<exception>                          x,
            in_<function<void( in_<exception> )>>   f
            ) -> bool
        {
            f( x );
            return for_each_nested_exception_in( x, f );
        }
    }  // namespace recursive

    namespace iterative {
        inline void rethrow_if_nested_pointee( in_<exception_ptr> p )
        {
            try {
                rethrow_exception( p );
            } catch( in_<exception> x ) {
                rethrow_if_nested( x );
            } catch( ... ) {
                ;
            }
        }

        inline auto for_each_nested_exception_in(
            in_<exception>                          final_x,
            in_<function<void( in_<exception> )>>   f
            ) -> bool
        {
            exception_ptr p_current = nullptr;
            for( ;; ) {
                try {
                    if( not p_current ) {
                        rethrow_if_nested( final_x );       // Rethrows a nested exception, if any.
                    } else {
                        rethrow_if_nested_pointee( p_current );
                    }
                    return true;
                } catch( in_<exception> x ) {
                    f( x );
                    p_current = current_exception();
                } catch( ... ) {
                    f( Unknown_exception{ current_exception() } );
                    return false;
                }
            }
        }

        inline auto for_each_exception_in(
            in_<exception>                          x,
            in_<function<void( in_<exception> )>>   f
            ) -> bool
        {
            f( x );
            return for_each_nested_exception_in( x, f );
        }
    }  // namespace iterative
}  // namespace machinery

namespace app {
    namespace m = machinery;
    #ifdef ITERATIVE
        namespace mx = m::iterative;
    #else
        namespace mx = m::recursive;            // Default.
    #endif
    using   m::in_, m::fail;
    using   mx::for_each_exception_in;
    using   std::cerr,                  // <iostream>
            std::exception;             // <stdexcept>

    void fundamental_operation() { fail( "app::fundamental_operation - Gah, unable to do it." ); }

    void intermediate()
    {
        try{
            fundamental_operation();
        } catch( ... ) {
            fail( "app::intermediate - Passing the buck." );
        }
    }

    void top_level()
    {
        try{
            intermediate();
        } catch( ... ) {
            fail( "app::top_level - I simply give up on this." );
        }
    }

    auto run() -> int
    {
        try{
            top_level();
            return EXIT_SUCCESS;
        } catch( in_<exception> x0 ) {
            for_each_exception_in( x0, [&]( in_<exception> x ) {
                cerr << (&x == &x0? "!" : "    because: ") << x.what() << '\n';
            } );
        } catch( ... ) {
            cerr << "!<unknown exception>\n";
        }
        return EXIT_FAILURE;
    }
}  // namespace app

auto main() -> int { return app::run(); }
