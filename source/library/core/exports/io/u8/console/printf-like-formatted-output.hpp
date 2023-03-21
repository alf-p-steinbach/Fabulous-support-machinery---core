#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/io/u8/console/output.hpp>         // Output_stream_id, output_to
#include <fsm/core/exports/text/sprintf-to-std-string.hpp>   // unsafe::ssprintf_to

namespace fabulous_support_machinery::console::_definitions {
    namespace fsm = fabulous_support_machinery;
    using   std::string_view,                       // <string_view>
            std::forward;                           // <utility>

    // Note:
    //
    // • field widths do not account for double width chars or multibyte encodings, i.e. non-ASCII.
    // • this functionality is not type safe.
    //
    // More type safe and Unicode-aware but limited formatting is provided by 'fixed-width-fields.hpp'.
    // More flexible type safe formatting (that includes fields) is provided via the “fmt” library.
    namespace unsafe {
        template< class... tp_Args >
        void cprintf_using_buffer(
            string&&                    buffer,
            const Output_stream_id      stream_id,
            const type_<const char*>    sprintf_format,
            tp_Args&&...                args
            )
        {
            fsm::unsafe::ssprintf_to( buffer, sprintf_format, forward<tp_Args>( args )... );
            output_to( stream_id, buffer );
        }

        template< class... tp_Args >
        void cprintf_to(
            const Output_stream_id      stream_id,
            const type_<const char*>    sprintf_format,
            tp_Args&&...                args
            )
        {
            cprintf_using_buffer( "", stream_id, sprintf_format, forward<tp_Args>( args )... );
        }

        template< class... tp_Args >
        void cprintf( const type_<const char*> sprintf_format, tp_Args&&... args )
        {
            cprintf_to( Stream_id::out, sprintf_format, forward<tp_Args>( args )... );
        }

        template< class... tp_Args >
        void cprintf_err( const type_<const char*> sprintf_format, tp_Args&&... args )
        {
            cprintf_to( Stream_id::err, sprintf_format, forward<tp_Args>( args )... );
        }
    }  // namespace unsafe

    namespace d = _definitions;
    namespace exports{
        namespace unsafe = d::unsafe;   // cprintf_using_buffer, cprintf_to, cprintf, cprintf_err
    }  // namespace exports
}  // namespace fabulous_support_machinery::console::_definitions

namespace fabulous_support_machinery::console   { using namespace _definitions::exports; }
