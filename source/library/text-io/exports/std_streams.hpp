#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/text-io/exports/Stream_id.hpp>                          // Stream_id
#include <fsm/text-io/exports/std_streams/Stream_io_over_.hpp>        // Stream_io_over_
#include <fsm/core/exports/constructs/type_builders.hpp>                 // in_
#include <fsm/core/exports/meta-type/class-kinds/Non_instantiable.hpp>   // Non_instantiable

#include <string>
#include <string_view>

namespace fabulous_support_machinery::u8::_definitions {

    using   std::string,            // <string>
            std::string_view;       // <string_view>

    class Std_streams_core
    {
        Std_streams_core() {}
        Std_streams_core( in_<Std_streams_core> ) = delete;

    public:
        static auto instance()
            -> Std_streams_core&
        {
            static Std_streams_core the_instance;
            return the_instance;
        }

        auto input_using_buffer( string&& buffer ) -> string;
        void output_to( Stream_id, in_<string_view> );
    };

    inline auto std_streams = Stream_io_over_( Std_streams_core::instance() );

    namespace d = _definitions;
    namespace exports{ using
        d::std_streams;
    }  // namespace exports
}  // namespace fabulous_support_machinery::u8::_definitions

namespace fabulous_support_machinery::u8 { using namespace _definitions::exports; }
