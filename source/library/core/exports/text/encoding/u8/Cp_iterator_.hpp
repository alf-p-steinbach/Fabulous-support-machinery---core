#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/basic-types/byte-types/Byte.hpp>                             // Byte
#include <fsm/core/exports/misc/support-for-collections/Iterator_pair_.hpp>                      // Iterator_pair_
#include <fsm/core/exports/misc/support-for-collections/size-functions.hpp>                      // int_size_of
#include <fsm/core/exports/mixins/Relational_operators_mixin_.hpp>                      // Relational_operators_mixin_
#include <fsm/core/exports/failure/expressing/FSM_FAIL.hpp>                    // FSM_FAIL
#include <fsm/core/exports/failure/detecting/FSM_STATIC_ASSERT.hpp>           // FSM_STATIC_ASSERT
#include <fsm/core/exports/text/encoding/u8/Cp_bytes_ref_.hpp>                        // u8::Cp_bytes_ref_, tag::*
#include <fsm/core/exports/text/encoding/u8/basic-sequence-functions.hpp>               // u8::*
#include <fsm/core/exports/meta-type/type-inspectors.hpp>  // bits_per_

#include <iterator>
#include <string>
#include <string_view>

namespace fabulous_support_machinery::u8::_definitions {
    using   std::iterator_traits, std::prev,        // <iterator>
            std::string, std::to_string,            // <string>
            std::string_view;                       // <string_view>

    struct Cp_iterator_base
    {
        struct Step_delta{ enum Enum{ backward = -1, forward = +1 }; };
    };
    
    template< class tp_Unit_iterator, bool tp_check = true >
    class Cp_iterator_core_:
        public Cp_iterator_base,
        public Relational_operators_mixin_<Cp_iterator_core_<tp_Unit_iterator, tp_check>>
    {
    public:
        using Unit_iterator     = tp_Unit_iterator;
        using Unit              = typename iterator_traits<Unit_iterator>::value_type;
        using Cp_bytes_ref    = Cp_bytes_ref_<Unit_iterator, tp_check>;

        // Required for e.g. use of `std::prev`, and generally for `std::iterator_traits`:
        using difference_type   = Size;
        using value_type        = Cp_bytes_ref;
        using pointer           = value_type*;
        using reference         = value_type&;
        using iterator_category	= std::bidirectional_iterator_tag;

        FSM_STATIC_ASSERT( bits_per_<Unit> == 8 );

    protected:
        Cp_bytes_ref    m_code_point_ref;

    public:
        constexpr Cp_iterator_core_( tags::Unchecked, const Unit_iterator it ):
            m_code_point_ref( tags::Unchecked(), it )
        {}

        constexpr Cp_iterator_core_( const Unit_iterator it ):
            m_code_point_ref( it )
        {}

        auto unit_iterator() const -> Unit_iterator     { return m_code_point_ref.unit_iterator(); }
        auto codepoint() const -> char32_t              { return m_code_point_ref.codepoint(); }
        auto sequence() const -> const Cp_bytes_ref&  { return m_code_point_ref; }

        friend auto compare( in_<Cp_iterator_core_> a, in_<Cp_iterator_core_> b )
            -> int
        { return static_cast<int>( a.m_code_point_ref.unit_pointer() - b.m_code_point_ref.unit_pointer() ); }

        template< Step_delta::Enum tp_delta >
        void step_()
        {
            if constexpr( tp_delta == Step_delta::forward ) {
                advance( m_code_point_ref, Byte_count{ m_code_point_ref.n_bytes() } );
            } else {
                Unit_iterator it = prev( m_code_point_ref.unit_iterator() );
                while( continuation_bytes::include( Byte( *it ) ) ) { --it; }
                if constexpr( tp_check ) {
                    hopefully( lead_bytes::include( Byte( *it ) ) )
                        or FSM_FAIL( "Invalid lead byte" );
                }
                m_code_point_ref = Cp_bytes_ref( tags::Unchecked(), it );
            }
        }

        template< Step_delta::Enum tp_delta >
        void skip_to_next_lead_bytes_( const int n_max_units = 42 )
        {
            Unit_iterator skipper = m_code_point_ref.unit_iterator();
            for( int i = 0; i < n_max_units; ++i ) {
                skipper += tp_delta;
                const Unit unit = *skipper;
                if( is_lead_bytes( unit ) ) {
                    m_code_point_ref = {skipper};
                    return;
                }
            }
            // TODO: <<-formatting of exception message below:
            FSM_FAIL( "No lead byte found within "s + to_string( n_max_units ) + " units." );
            for( ;; ) {}    // Should not get here.
        }

        void step_forward()     { step_<Step_delta::forward>(); }
        void step_backward()    { step_<Step_delta::backward>(); }
    };
    
    using Cp_iterator_core = Cp_iterator_core_<const char*>;

    template< class tp_Unit_iterator, bool tp_check = true >
    class Cp_iterator_:
        public Cp_iterator_core_< tp_Unit_iterator, tp_check >
    {
        // TODO: standard-iterator stuff.
    public:
        using Base = Cp_iterator_core_<tp_Unit_iterator, tp_check>;
        using Base::Cp_iterator_core_;      // Inherit the constructors.
        using Self = Cp_iterator_;

        using typename Base::Cp_bytes_ref;
        using Value = Cp_bytes_ref;
        
        using Base::sequence;
        using Base::step_forward;
        using Base::step_backward;
        
        auto operator*() const  -> const Value& { return this->m_code_point_ref; }
        auto operator->() const -> const Value* { return &this->m_code_point_ref; }

        auto operator++() -> Self& { step_forward(); return *this; }
        auto operator--() -> Self& { step_backward();  return *this; }

        auto operator++( int )
            -> Self
        {
            const Self original = *this;
            step_forward();
            return original;
        }
        
        auto operator--( int )
            -> Self
        {
            const Self original = *this;
            step_backward();
            return original;
        }
    };
    
    using Cp_iterator = Cp_iterator_<const char*>;

    template<
        class tp_Unit_iterator,
        class tp_It = Cp_iterator_< tp_Unit_iterator >
        >
    constexpr auto to_code_point_iterators( in_<tp_Unit_iterator> it_first, const int n )
        -> Iterator_pair_< tp_It >
    { return {tp_It( it_first ), tp_It( tags::Unchecked(), it_first + n )}; }

    constexpr auto to_code_point_iterators( in_<string_view> s )
        -> Iterator_pair_< Cp_iterator >
    { return to_code_point_iterators( s.data(), int_size_of( s ) ); }
        
    namespace d = _definitions;
    namespace exports { using
        d::Cp_iterator_core_, d::Cp_iterator_core,
        d::Cp_iterator_, d::Cp_iterator,
        d::to_code_point_iterators;
    }  // namespace exports
}  // namespace fabulous_support_machinery::u8::_definitions

namespace fabulous_support_machinery::u8 { using namespace _definitions; }
