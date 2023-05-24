#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/headers/+std-cpp-language.hpp>

#include <fsm/core/headers/failure/detecting/FSM_STATIC_ASSERT.hpp>             // FSM_STATIC_ASSERT
#include <fsm/core/headers/misc/iterator-classification.hpp>                    // is_tagged_as_forward_
#include <fsm/core/headers/mixins/Relational_operators_mixin_.hpp>              // Relational_operators_mixin_
#include <fsm/core/headers/text/encoding/u8/basic-sequence-functions.hpp>       // u8::*
#include <fsm/core/headers/text/encoding/u8/Code_point_inspectors_mixin_.hpp>   // Code_point_inspectors_mixin_, Unit_iterator_of_t_

// #include <algorithm>            // std::min
#include <iterator>             // std::iterator_traits, std::next
#include <string>               // std::string
#include <string_view>          // std::string_view

#include <string.h>             // memcmp

namespace fsm_definitions::u8 {
    namespace fsm = fabulous_support_machinery;
    // FSM_NS_FROM( fsm::u8, byte_sequence );         // text/encoding/u8/basic-sequence-functions.hpp
    // FSM_NS_FROM( fsm::u8, lead_bytes );             // text/encoding/u8/basic-sequence-functions.hpp

    using   fsm::Byte,
            fsm::in_,
            fsm::is_tagged_as_forward_,
            fsm::Relational_operators_mixin_;

    using   std::min,                                           // <algorithm>
            std::iterator_traits, std::next,                    // <iterator>
            std::string,                                        // <string>
            std::string_view;                                   // <string_view>

    template< class > struct Unit_iterator_of_t_;

    template< class Type >
    using Unit_iterator_of_ = typename Unit_iterator_of_t_<Type>::T;

    template< class Derived >
    class Code_point_inspectors_mixin_:
        public Relational_operators_mixin_<Code_point_inspectors_mixin_<Derived>>
    {
    public:
        using Unit_iterator     = Unit_iterator_of_<Derived>;
        FSM_STATIC_ASSERT( is_tagged_as_forward_<Unit_iterator> );      // That includes random access iterators.
        
        using Unit              = typename iterator_traits<Unit_iterator>::value_type;
        FSM_STATIC_ASSERT( sizeof( Unit ) == 1 );

    private:
        auto self() const
            -> const Derived&
        { return static_cast<const Derived&>( *this ); }

        auto it_start() const -> Unit_iterator { return self().unit_iterator(); }

    public:
        auto first_unit() const -> Unit             { return *it_start(); }

        auto n_bytes() const    -> int              { return lead_bytes::sequence_length_of( Byte( first_unit() ) ); }
        auto begin() const      -> Unit_iterator    { return it_start(); }
        auto end() const        -> Unit_iterator    { return next( it_start(), n_bytes() ); }

        auto str() const        -> string           { return string( it_start(), n_bytes() ); }

        // Requires contiguous iterator:
        auto unit_pointer() const -> const Unit*    { return &*it_start(); }
        auto char_pointer() const -> const char*    { return reinterpret_cast<const char*>( unit_pointer() ); }
        auto as_number() const  -> char32_t         { return byte_sequence::to_codepoint( it_start() ); }
        auto sv() const         -> string_view      { return string_view( char_pointer(), n_bytes() ); }
    };

    template< class Derived >
    inline auto compare(
        in_<Code_point_inspectors_mixin_<Derived>>  a,
        in_<Code_point_inspectors_mixin_<Derived>>  b
        ) -> int
    {
        // UTF-8 sequences compare lexicographically just like their Unicode code points.
        // If one sequence is shorter then there's a difference within the shorter length.
        const bool bytes_are_contiguous = true;     // TODO: check via iterator properties
        if constexpr( bytes_are_contiguous ) {
            return ::memcmp(
                a.unit_pointer(), b.unit_pointer(), min( a.n_bytes(), b.n_bytes() )
                );
        } else {
            throw 666;      // TODO
        }
    }

    template< class Derived >
    using Sequence_inspectors_mixin = Code_point_inspectors_mixin_<Derived>;

    namespace x = u8;
    namespace exports { using
        x::Code_point_inspectors_mixin_,
        x::Sequence_inspectors_mixin;
    }  // namespace exports
}  // namespace fsm_definitions::u8

namespace fabulous_support_machinery{
    // `u8::` stuff is intentionally not available unqualified in fsm namespace.

    // Not a simple equate because may need to be an extension of earlier declared namespace.
    namespace u8{
        using namespace fsm_definitions::u8::exports;
    }  // namespace u8
}  // namespace fabulous_support_machinery
