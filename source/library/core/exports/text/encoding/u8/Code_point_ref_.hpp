#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/text/encoding/u8/basic-sequence-functions.hpp>    // u8::*
#include <fsm/core/exports/text/encoding/u8/Byte_count.hpp>                  // Byte_count
#include <fsm/core/exports/text/encoding/u8/Code_point_inspectors_mixin_.hpp>  // Code_point_inspectors_mixin_

#include <iterator>             // iterator_traits
#include <string>               // string
#include <string_view>          // string_view

namespace tags {
    using Unchecked = struct Unchecked_tag*;
}  // namespace tags

namespace fabulous_support_machinery::u8::_definitions {
    using   std::iterator_traits,       // <iterator>
            std::string,                // <string>
            std::string_view;           // <string_view>

    template< class, bool > class Code_point_ref_;

    template< class tp_Unit_iterator, bool tp_check >
    struct Unit_iterator_of_t_< Code_point_ref_< tp_Unit_iterator, tp_check > >
    {
        using T = tp_Unit_iterator;
    };

    template< class tp_Unit_iterator, bool tp_check = true >
    class Code_point_ref_:
        public Code_point_inspectors_mixin_< Code_point_ref_< tp_Unit_iterator, tp_check > >
    {
    public:
        using Unit_iterator     = tp_Unit_iterator;
        using Unit              = typename iterator_traits<Unit_iterator>::value_type;

    private:
        using Inspectors = Code_point_inspectors_mixin_< Code_point_ref_ >;

        Unit_iterator   m_it_first;

    public:
        constexpr Code_point_ref_( tags::Unchecked, const Unit_iterator it_first ):
            m_it_first( it_first )
        {}

        constexpr Code_point_ref_( const Unit_iterator it_first ):
            m_it_first( tp_check? byte_sequences::checked( it_first ) : it_first )
        {}
 
        constexpr auto unit_iterator() const -> Unit_iterator { return m_it_first; }

        using   Inspectors::first_unit, Inspectors::n_bytes,
                Inspectors::begin, Inspectors::end, Inspectors::unit_pointer, Inspectors::char_pointer,
                Inspectors::cp_number, Inspectors::sv, Inspectors::str;
    };
    
    using Code_point_ref = Code_point_ref_<const char*>;

    template< class tp_Unit_iterator, bool tp_check >
    inline auto advanced_by(
        const Byte_count                                    delta,
        in_<Code_point_ref_<tp_Unit_iterator, tp_check>>      seq
        ) -> Code_point_ref_<tp_Unit_iterator, tp_check>
    { return {seq.unit_iterator() + delta.value}; }     // TODO:

    template< class tp_Unit_iterator, bool tp_check >
    void advance( Code_point_ref_<tp_Unit_iterator, tp_check>& seq, const Byte_count delta )
    {
        seq = {seq.unit_iterator() + delta.value};
    }

    namespace d = _definitions;
    namespace exports { using
        d::Code_point_ref_, d::Code_point_ref,
        d::advance;
    }  // namespace exports
}  // namespace fabulous_support_machinery::u8::_definitions

namespace fabulous_support_machinery::u8 { using namespace _definitions; }
