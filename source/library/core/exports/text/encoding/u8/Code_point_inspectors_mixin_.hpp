#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/failure/detecting/FSM_STATIC_ASSERT.hpp>             // FSM_STATIC_ASSERT
#include <fsm/core/exports/mixins/Relational_operators_mixin_.hpp>              // Relational_operators_mixin_
#include <fsm/core/exports/text/encoding/u8/basic-sequence-functions.hpp>       // u8::*

// #include <algorithm>            // std::min
#include <iterator>             // std::iterator_traits
#include <string>               // std::string
#include <string_view>          // std::string_view

#include <string.h>             // memcmp

namespace fabulous_support_machinery::u8::_definitions {
    using   std::min,                   // <algorithm>
            std::iterator_traits,       // <iterator>
            std::string,                // <string>
            std::string_view;           // <string_view>

    template< class > struct Unit_iterator_of_t_;

    template< class Type >
    using Unit_iterator_of_ = typename Unit_iterator_of_t_<Type>::T;

    template< class Derived >
    class Code_point_inspectors_mixin_:
        public Relational_operators_mixin_<Code_point_inspectors_mixin_<Derived>>
    {
    public:
        using Unit_iterator     = Unit_iterator_of_<Derived>;
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
        auto end() const        -> Unit_iterator    { return it_start() + n_bytes(); }
        
        auto unit_pointer() const -> const Unit*    { return &*it_start(); }
        auto char_pointer() const -> const char*    { return reinterpret_cast<const char*>( unit_pointer() ); }

        auto as_number() const  -> char32_t         { return byte_sequences::to_codepoint( it_start() ); }
        auto sv() const         -> string_view      { return string_view( char_pointer(), n_bytes() ); }
        auto str() const        -> string           { return string( char_pointer(), n_bytes() ); }
    };

    template< class Derived >
    inline auto compare(
        in_<Code_point_inspectors_mixin_<Derived>>  a,
        in_<Code_point_inspectors_mixin_<Derived>>  b
        ) -> int
    {
        // UTF-8 sequences compare lexicographically just like their Unicode code points.
        // If one sequence is shorter then there's a difference within the shorter length.
        return ::memcmp(
            a.unit_pointer(), b.unit_pointer(), min( a.n_bytes(), b.n_bytes() )
            );
    }

    template< class Derived >
    using Sequence_inspectors_mixin = Code_point_inspectors_mixin_<Derived>;

    namespace d = _definitions;
    namespace exports { using
        d::Code_point_inspectors_mixin_,
        d::Sequence_inspectors_mixin;
    }  // namespace exports
}  // namespace fabulous_support_machinery::u8::_definitions

namespace fabulous_support_machinery::u8 { using namespace _definitions; }
