// Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <iterator>

namespace fabulous_support_machinery::u16::_definitions {
    using   std::iterator_traits;

    template< class tp_Unit_iterator >
    constexpr byte_sequences::to_codepoint( const tp_Unit_iterator it )
        -> char32_t
    {
        const Unit unit = *it;
        // ...
    }

    template< class tp_Unit_iterator >
    class Cp_iterator_
    {
        tp_Unit_iterator   m_it;

    public:
        using Unit  = typename iterator_traits<tp_Unit_iterator>::value_type;
        
        Cp_iterator_( const tp_Unit_iterator it ): m_it( it ) {}
        
        auto encoding() const -> tp_Unit_iterator { return m_it; }

        auto operator*() const
            -> char32_t
        {
            return byte_sequences::to_codepoint( m_it );
        }
            
        void advance()
        {
            
        }
    };

}  // namespace fabulous_support_machinery::u16::_definitions
