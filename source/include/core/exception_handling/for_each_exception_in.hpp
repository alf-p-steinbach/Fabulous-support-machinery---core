#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/parameter_passing/in_.hpp>           // in_

#include <exception>
#include <functional>
#include <stdexcept>

namespace fsm_definitions {
    using   fsm::in_;                   // parameter_passing/in_
    using   std::exception_ptr, std::make_exception_ptr, std::rethrow_exception,    // <exception>
            std::function,                          // <functional>
            std::exception;                         // <stdexcept>

    namespace exception_handling
    {
        class Unknown_exception:
            public exception
        {
            exception_ptr   m_ptr;

        public:
            Unknown_exception( in_<exception_ptr> p ): m_ptr( p ) {}
            auto ptr() const -> exception_ptr { return m_ptr; }
        };

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

        inline auto for_each_exception_in(
            in_<exception>                      final_x,
            function<void( in_<exception> )>    f
            ) -> bool
        {
            exception_ptr p_current = nullptr;
            f( final_x );
            for( ;; ) {
                try {
                    if( not p_current ) {
                        rethrow_if_nested( final_x );
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
    }
}  // namespace fsm_definitions

namespace fsm {
    inline namespace exception_handling { using namespace fsm_definitions::exception_handling; }
}  // namespace fsm
