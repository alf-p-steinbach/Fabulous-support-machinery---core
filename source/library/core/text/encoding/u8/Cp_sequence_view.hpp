#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/text/encoding/u8/Cp_iterator_.hpp>

#include <iterator>

namespace fsm_definitions::u8 {
    namespace fsm = fabulous_support_machinery;
    
    using   fsm::in_,                   // constructs/declarations/type_builders.hpp
            fsm::Iterator_pair_,        // misc/support-for-collections/Iterator_pair_.hpp
            fsm::u8::Cp_iterator, fsm::u8::to_code_point_iterators; // text/encoding/u8/Cp_iterator_.hpp

    using   std::distance,              // <iterator>
            std::string,                // <string>     
            std::string_view;           // <string_view>
    
    class Cp_sequence_view:
        public Iterator_pair_< Cp_iterator >
    {
        using Base = Iterator_pair_< Cp_iterator >;

    public:
        Cp_sequence_view( in_<string_view> s ):
            Base( to_code_point_iterators( s ) )
        {}

        auto n_bytes() const
            -> int
        { return static_cast<int>( distance( begin().unit_iterator(), end().unit_iterator() ) ); }

        auto char_pointer() const
            -> const char*
        { return begin().unit_iterator(); }     // TODO: ?

        auto sv() const     -> string_view  { return string_view( char_pointer(), n_bytes() ); }
        auto str() const    -> string       { return string( char_pointer(), n_bytes() ); }
    };

    namespace x = u8;
    namespace exports { using
        x::Cp_sequence_view;
    }  // namespace exports
}  // namespace fsm_definitions::u8

namespace fabulous_support_machinery{
    // `u8::` stuff is intentionally not available unqualified in fsm namespace.

    // Not a simple equate because may need to be an extension of earlier declared namespace.
    namespace u8{
        using namespace fsm_definitions::u8::exports;
    }  // namespace u8
}  // namespace fabulous_support_machinery
