#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/failure/detecting/FSM_STATIC_ASSERT.hpp>                 // FSM_STATIC_ASSERT
#include <fsm/core/text/encoding/u8/basic-sequence-functions.hpp>           // u8::*
#include <fsm/core/text/encoding/u8/Code_point_inspectors_mixin_.hpp>       // Code_point_inspectors_mixin_, Unit_iterator_of_t_
#include <fsm/core/constructs/declarations/type_builders.hpp>               // array_of_, const_

#include <algorithm>            // copy
#include <iterator>             // iterator_traits
#include <string>               // string
#include <string_view>          // string_view

#include <assert.h>             // assert

namespace tags {
    using Unchecked = struct Unchecked_tag*;
}  // namespace tags

namespace fsm_definitions::u8 {
    namespace fsm = fabulous_support_machinery;

    using   fsm::array_of_, fsm::const_;

    using   std::copy,                  // <algorithm>
            std::iterator_traits,       // <iterator>
            std::string,                // <string>
            std::string_view;           // <string_view>

    template< class, bool > class Cp_bytes_;

    template< class tp_Unit_iterator, bool tp_check >
    struct Unit_iterator_of_t_< Cp_bytes_< tp_Unit_iterator, tp_check > >
    {
        using T = tp_Unit_iterator;
    };

    // TODO: rename to Cp_bytes_
    template< class tp_Unit_iterator, bool tp_check = true >
    class Cp_bytes_:
        public Code_point_inspectors_mixin_< Cp_bytes_< tp_Unit_iterator, tp_check > >
    {
    public:
        using Unit_iterator     = tp_Unit_iterator;
        using Unit              = typename iterator_traits<Unit_iterator>::value_type;
        FSM_STATIC_ASSERT( sizeof( Unit ) == 1 );

        static constexpr int max_length = 4;
        FSM_STATIC_ASSERT( max_length == byte_sequence::max_length );

    private:
        using Inspectors = Code_point_inspectors_mixin_< Cp_bytes_ >;
        array_of_<max_length, Unit>     m_units;

    public:
        Cp_bytes_(
            tags::Unchecked         ,
            const_<const Unit*>     p_first,
            const int               n_bytes
            )
        {
            // assert( n_bytes <= max_length );
            copy( p_first, p_first + n_bytes, m_units );
        }

        Cp_bytes_( tags::Unchecked, const_<const Unit*> p_first ):
            Cp_bytes_( tags::Unchecked(), p_first, lead_bytes::sequence_length_of( *p_first ) )
        {}

        Cp_bytes_( const_<const Unit*> p_first ):
            Cp_bytes_(
                tags::Unchecked(),
                tp_check? byte_sequence::checked( p_first ) : p_first
                )
        {}

        Cp_bytes_( const char32_t code )
        {
            byte_sequence::to_sequence_at( m_units, code );
        }

        // CRTP callback for inspectors:
        auto unit_iterator() const -> const Unit* { return &m_units[0]; }

        using   Inspectors::first_unit, Inspectors::n_bytes,
                Inspectors::begin, Inspectors::end, Inspectors::unit_pointer, Inspectors::char_pointer,
                Inspectors::as_number, Inspectors::sv, Inspectors::str;
    };

    using Cp_bytes = Cp_bytes_<const char*>;

    namespace x = u8;
    namespace exports { using
        x::Cp_bytes_,
        x::Cp_bytes;
    }  // namespace exports
}  // namespace fsm_definitions::u8

namespace fabulous_support_machinery{
    // `u8::` stuff is intentionally not available unqualified in fsm namespace.

    // Not a simple equate because may need to be an extension of earlier declared namespace.
    namespace u8{
        using namespace fsm_definitions::u8::exports;
    }  // namespace u8
}  // namespace fabulous_support_machinery
