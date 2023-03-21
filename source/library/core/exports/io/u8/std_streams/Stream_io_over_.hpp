#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/type_builders.hpp>     // in_
#include <fsm/core/exports/io/u8/Stream_id.hpp>              // Stream_id

#include <string>
#include <string_view>
#include <utility>

//    struct Core: Non_instantiable
//    {
//        auto input_using_buffer( string&& buffer ) -> string;
//        void output_to( Stream_id, in_<string_view> );
//    };

namespace fabulous_support_machinery::u8::_definitions {

    using   std::string,            // <string>
            std::string_view,       // <string_view>
            std::move;

    template< class Core >
    class Stream_io_over_
    {
        Core&   m_core;
        
    public:
        Stream_io_over_( Core& core ):
            m_core( core )
        {}

        auto input_using_buffer( string&& buffer )
            -> string
        { return m_core.input_using_buffer( move( buffer ) ); }
        
        void output_to( const Stream_id stream_id, in_<string_view> s )
        {
            m_core.output_to( stream_id, s );
        }

        auto input() -> string                  { return input_using_buffer( "" ); }
        void output( in_<string_view> s )       { output_to( Stream_id::out, s ); }
        void output_err( in_<string_view> s )   { output_to( Stream_id::err, s ); }
    };
    
    namespace d = _definitions;
    namespace exports{ using
        d::Stream_io_over_;
    }  // namespace exports
}  // namespace fabulous_support_machinery::u8::_definitions

namespace fabulous_support_machinery::u8 { using namespace _definitions::exports; }
