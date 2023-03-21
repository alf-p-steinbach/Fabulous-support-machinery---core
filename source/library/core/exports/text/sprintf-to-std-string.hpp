#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/collections-support/size-functions.hpp>    // int_capacity_of
#include <fsm/core/exports/constructs/type_builders.hpp>                         // in_

#include <string>
#include <utility>

#include <stddef.h>         // size_t
#include <stdio.h>          // snprintf

namespace fabulous_support_machinery::_definitions {
    using   std::string,                // <string>
            std::forward, std::move;    // <utility>

    namespace unsafe {
        constexpr int default_buffer_capacity = 128;    // Enough for most lines of output.

        template< class... Args >
        void ssprintf_to(
            string&                     result,
            const type_<const char*>    format,
            Args&&...                   args
            )
        {
            int capacity = int_capacity_of( result );
            if( capacity <= 1 ) {
                result.reserve( default_buffer_capacity );
                capacity = int_capacity_of( result );
            }
            int buffer_size = capacity - 1;
            result.resize( buffer_size );
            const int n_chars = snprintf( result.data(), buffer_size, format, forward<Args>( args )... );
            if( n_chars >= buffer_size ) {
                buffer_size = n_chars + 1;
                result.resize( buffer_size );
                snprintf( result.data(), buffer_size, format, forward<Args>( args )... );
            }
            result.resize( n_chars );
        }

        template< class... Args >
        auto ssprintf_using_buffer(
            string&&                    buffer,
            const type_<const char*>    format,
            Args&&...                   args
            )
            -> string
        {
            sprintf_to( buffer, format, forward<Args>( args )... );
            return move( buffer );
        }

        template< class... Args >
        auto ssprintf( const type_<const char*> format, Args&&... args )
            -> string
        { return sprintf_using_buffer( "", format, forward<Args>( args )... ); }
    }  // namespace unsafe

    namespace d = _definitions;
    namespace exports{
        namespace unsafe = d::unsafe;
    }  // namespace exports
}  // namespace fabulous_support_machinery::console::_definitions

namespace fabulous_support_machinery    { using namespace _definitions::exports; }
