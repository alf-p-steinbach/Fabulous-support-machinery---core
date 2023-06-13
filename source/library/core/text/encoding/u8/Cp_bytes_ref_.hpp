#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/text/encoding/u8/basic-sequence-functions.hpp>       // u8::*
#include <fsm/core/text/encoding/u8/Code_point_inspectors_mixin_.hpp>   // Code_point_inspectors_mixin_

#include <iterator>             // iterator_traits
#include <string>               // string
#include <string_view>          // string_view

namespace tag {
    using Unchecked = struct Unchecked_tag*;
}  // namespace tag

namespace fsm_definitions::u8 {
    namespace fsm = fabulous_support_machinery;
    // FSM_NS_FROM( fsm::u8, byte_sequence );         // text/encoding/u8/basic-sequence-functions.hpp

    using   fsm::in_,                               // constructs/declarations/type_builders.hpp
            fsm::u8::Code_point_inspectors_mixin_;  // text/encoding/u8/Code_point_inspectors_mixin_.hpp

    using   std::iterator_traits,           // <iterator>
            std::string,                    // <string>
            std::string_view;               // <string_view>

    struct Byte_count { int value; };

    template< class, bool > class Cp_bytes_ref_;

    template< class Basic_unit_iterator, bool check >
    struct Unit_iterator_of_t_< Cp_bytes_ref_< Basic_unit_iterator, check > >
    {
        using T = Basic_unit_iterator;
    };

    template< class Basic_unit_iterator, bool check = true >
    class Cp_bytes_ref_:
        public Code_point_inspectors_mixin_< Cp_bytes_ref_< Basic_unit_iterator, check > >
    {
    public:
        using Unit_iterator     = Basic_unit_iterator;
        using Unit              = typename iterator_traits<Unit_iterator>::value_type;

    private:
        using Inspectors = Code_point_inspectors_mixin_< Cp_bytes_ref_ >;

        Unit_iterator   m_it_first;

    public:
        constexpr Cp_bytes_ref_( tag::Unchecked, const Unit_iterator it_first ):
            m_it_first( it_first )
        {}

        constexpr Cp_bytes_ref_( const Unit_iterator it_first ):
            m_it_first( check? byte_sequence::checked( it_first ) : it_first )
        {}
 
        constexpr auto unit_iterator() const -> Unit_iterator { return m_it_first; }

        using   Inspectors::first_unit,
                Inspectors::n_bytes,
                Inspectors::begin,
                Inspectors::end,
                Inspectors::unit_pointer,
                Inspectors::char_pointer,
                Inspectors::as_number,
                Inspectors::sv,
                Inspectors::str;
    };

    using Cp_bytes_ref = Cp_bytes_ref_<const char*>;

    template< class Basic_unit_iterator, bool check >
    inline auto advanced_by(
        const Byte_count                                    delta,
        in_<Cp_bytes_ref_<Basic_unit_iterator, check>>      seq
        )
        -> Cp_bytes_ref_<Basic_unit_iterator, check>
    {
        // TODO: checking
        return {seq.unit_iterator() + delta.value};
    }

    template< class Basic_unit_iterator, bool check >
    void advance( Cp_bytes_ref_<Basic_unit_iterator, check>& seq, const Byte_count delta )
    {
        seq = {seq.unit_iterator() + delta.value};
    }

    namespace x = u8;
    namespace exports { using
        x::Cp_bytes_ref_,
        x::Cp_bytes_ref,
        x::advance;
    }  // namespace exports
}  // namespace fsm_definitions::u8

namespace fabulous_support_machinery{
    // `u8::` stuff is intentionally not available unqualified in fsm namespace.

    // Not a simple equate because may need to be an extension of earlier declared namespace.
    namespace u8{
        using namespace fsm_definitions::u8::exports;
    }  // namespace u8
}  // namespace fabulous_support_machinery
