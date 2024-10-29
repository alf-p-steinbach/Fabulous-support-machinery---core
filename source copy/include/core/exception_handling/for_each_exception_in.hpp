#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/exception_handling/rethrow_nested_if_any_in.hpp>     // rethrow_nested_if_any_in
#include <fsm/core/parameter_passing/in_.hpp>                           // in_

#include <exception>
#include <functional>
#include <stdexcept>

namespace fsm_definitions {
    using   fsm::rethrow_nested_if_any_in,      // excpetion_handling/rethrow_nested_if_any_in.hpp
             fsm::in_;                          // parameter_passing/in_
    using   std::exception_ptr, std::make_exception_ptr, std::rethrow_exception,    // <exception>
            std::function,                      // <functional>
            std::exception;                     // <stdexcept>

    namespace exception_handling
    {
        class Unknown_exception:
            public exception
        {
            exception_ptr   m_ptr;

        public:
            Unknown_exception( in_<exception_ptr> p ): m_ptr( p ) {}
            auto ptr() const -> exception_ptr { return m_ptr; }
            auto what() const noexcept -> const char* override { return "<unknown exception>"; }
        };

        inline auto for_each_nested_exception_in(
            in_<exception>                      x,
            function<void( in_<exception> )>    f
            ) -> bool
        {
            try {
                rethrow_nested_if_any_in( x );
                return true;
            } catch( in_<exception> nested_x ) {
                f( nested_x );
                return for_each_nested_exception_in( nested_x, f );
            } catch( ... ) {
                f( Unknown_exception{ current_exception() } );
                return false;
            }
        }

        #if 0       // Iterative version.
            inline void rethrow_if_nested_pointee( in_<exception_ptr> p )
            {
                try {
                    rethrow_exception( p );
                } catch( in_<exception> x ) {
                    rethrow_nested_if_any_in( x );
                } catch( ... ) {
                    ;
                }
            }

            inline auto for_each_nested_exception_in(
                in_<exception>                      final_x,
                function<void( in_<exception> )>    f
                ) -> bool
            {
                exception_ptr p_current = nullptr;
                for( ;; ) {
                    try {
                        if( not p_current ) {
                            rethrow_nested_if_any_in( final_x );    // Rethrows a nested exception, if any.
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
        #endif

        inline auto for_each_exception_in(
            in_<exception>                      final_x,
            function<void( in_<exception> )>    f
            ) -> bool
        {
            f( final_x );
            return for_each_nested_exception_in( final_x, f );
        }
    }  // namespace exception_handling
}  // namespace fsm_definitions

namespace fsm {
    inline namespace exception_handling { using namespace fsm_definitions::exception_handling; }
}  // namespace fsm
