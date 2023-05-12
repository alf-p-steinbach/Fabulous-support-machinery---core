#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/failure/detecting/FSM_STATIC_ASSERT.hpp>               // FSM_STATIC_ASSERT
#include <fsm/core/exports/text/encoding/u8/basic-sequence-functions.hpp>        // u8::*
#include <fsm/core/exports/text/encoding/u8/Byte_count.hpp>                      // Byte_count
#include <fsm/core/exports/text/encoding/u8/Code_point_inspectors_mixin_.hpp>    // Code_point_inspectors_mixin_
#include <fsm/core/exports/constructs/declarations/type_builders.hpp>                                    // array_of_, const_

#include <algorithm>            // copy
#include <iterator>             // iterator_traits
#include <string>               // string
#include <string_view>          // string_view

#include <assert.h>             // assert

namespace tags {
    using Unchecked = struct Unchecked_tag*;
}  // namespace tags

namespace fabulous_support_machinery::u8::_definitions {
    using   std::copy,                  // <algorithm>
            std::iterator_traits,       // <iterator>
            std::string,                // <string>
            std::string_view;           // <string_view>

    template< class, bool > class Code_point_;

    template< class tp_Unit_iterator, bool tp_check >
    struct Unit_iterator_of_t_< Code_point_< tp_Unit_iterator, tp_check > >
    {
        using T = tp_Unit_iterator;
    };

    template< class tp_Unit_iterator, bool tp_check = true >
    class Code_point_:
        public Code_point_inspectors_mixin_< Code_point_< tp_Unit_iterator, tp_check > >
    {
    public:
        using Unit_iterator     = tp_Unit_iterator;
        using Unit              = typename iterator_traits<Unit_iterator>::value_type;
        FSM_STATIC_ASSERT( sizeof( Unit ) == 1 );

        static constexpr int max_length = 4;
        FSM_STATIC_ASSERT( max_length == byte_sequences::max_length );

    private:
        using Inspectors = Code_point_inspectors_mixin_< Code_point_ >;
        array_of_<max_length, Unit>     m_units;

    public:
        Code_point_(
            tags::Unchecked         ,
            const_<const Unit*>     p_first,
            const int               n_bytes
            )
        {
            // assert( n_bytes <= max_length );
            copy( p_first, p_first + n_bytes, m_units );
        }

        Code_point_( tags::Unchecked, const_<const Unit*> p_first ):
            Code_point_( tags::Unchecked(), p_first, lead_bytes::sequence_length_of( *p_first ) )
        {}

        Code_point_( const_<const Unit*> p_first ):
            Code_point_(
                tags::Unchecked(),
                tp_check? byte_sequences::checked( p_first ) : p_first
                )
        {}
        
        Code_point_( const char32_t code )
        {
            byte_sequences::to_sequence_at( m_units, code );
        }

        // CRTP callback for inspectors:
        auto unit_iterator() const -> const Unit* { return &m_units[0]; }

        using   Inspectors::first_unit, Inspectors::n_bytes,
                Inspectors::begin, Inspectors::end, Inspectors::unit_pointer, Inspectors::char_pointer,
                Inspectors::as_number, Inspectors::sv, Inspectors::str;
    };
    
    using Code_point = Code_point_<const char*>;


    namespace d = _definitions;
    namespace exports { using
        d::Code_point_, d::Code_point;
    }  // namespace exports
}  // namespace fabulous_support_machinery::u8::_definitions

namespace fabulous_support_machinery::u8 { using namespace _definitions; }
