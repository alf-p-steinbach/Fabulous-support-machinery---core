#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/basic-types/byte-types/Byte.hpp>                     // Byte
#include <fsm/core/misc/support-for-collections/Iterator_pair_.hpp>     // Iterator_pair_
#include <fsm/core/misc/support-for-collections/size-functions.hpp>     // int_size_of
#include <fsm/core/mixins/Relational_operators_mixin_.hpp>              // Relational_operators_mixin_
#include <fsm/core/failure/expressing/FSM_FAIL.hpp>                     // FSM_FAIL
#include <fsm/core/failure/detecting/FSM_STATIC_ASSERT.hpp>             // FSM_STATIC_ASSERT
#include <fsm/core/text/encoding/u8/Cp_bytes_ref_.hpp>                  // u8::Cp_bytes_ref_, tag::*
#include <fsm/core/text/encoding/u8/basic-sequence-functions.hpp>       // u8::*
#include <fsm/core/meta-type/type-inspectors.hpp>                       // bits_per_

#include <iterator>
#include <string>
#include <string_view>

namespace fsm_definitions::u8 {
    namespace fsm = fabulous_support_machinery;
    
    using   fsm::Byte,                              // basic-types/byte-types/Byte.hpp
            fsm::in_,                               // constructs/declarations/type_builders.hpp
            fsm::hopefully,                         // failure/detecting/hopefully.hpp
            fsm::bits_per_,                         // meta-type/type-inspectors.hpp
            fsm::Iterator_pair_,                    // misc/support-for-collections/Iterator_pair_.hpp
            fsm::Size, fsm::int_size_of,            // misc/support-for-collections/size-functions.hpp
            fsm::Relational_operators_mixin_,       // mixins/Relational_operators_mixin_.hpp
            fsm::u8::Cp_bytes_ref_;                 // text/encoding/u8/Cp_bytes_ref_.hpp

    using   std::iterator_traits, std::prev,        // <iterator>
            std::string, std::to_string,            // <string>
            std::string_view;                       // <string_view>

    struct Cp_iterator_common_stuff
    {
        struct Step_delta{ enum Enum{ backward = -1, forward = +1 }; };
    };
    
    template< class Basic_unit_iterator, bool check = true >
    class Cp_iterator_core_:
        public Cp_iterator_common_stuff,
        public Relational_operators_mixin_<Cp_iterator_core_<Basic_unit_iterator, check>>
    {
    public:
        using Unit_iterator     = Basic_unit_iterator;
        using Unit              = typename iterator_traits<Unit_iterator>::value_type;
        using Cp_bytes_ref      = Cp_bytes_ref_<Unit_iterator, check>;

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
        constexpr Cp_iterator_core_( tag::Unchecked, const Unit_iterator it ):
            m_code_point_ref( tag::Unchecked(), it )
        {}

        constexpr Cp_iterator_core_( const Unit_iterator it ):
            m_code_point_ref( it )
        {}

        auto unit_iterator() const -> Unit_iterator     { return m_code_point_ref.unit_iterator(); }
        auto codepoint() const -> char32_t              { return m_code_point_ref.codepoint(); }
        auto sequence() const -> const Cp_bytes_ref&    { return m_code_point_ref; }

        friend auto compare( in_<Cp_iterator_core_> a, in_<Cp_iterator_core_> b )
            -> int
        { return static_cast<int>( a.m_code_point_ref.unit_pointer() - b.m_code_point_ref.unit_pointer() ); }

        void step_forward()
        {
            advance( m_code_point_ref, Byte_count{ m_code_point_ref.n_bytes() } );
        }

        void step_backward()
        {
            Unit_iterator it = prev( m_code_point_ref.unit_iterator() );
            while( fsm::u8::is_continuation_byte( Byte( *it ) ) ) {
                --it;
            }
            if constexpr( check ) {
                hopefully( fsm::u8::is_lead_byte( Byte( *it ) ) )    // TODO: naming, "include" is ungood
                    or FSM_FAIL( "Invalid lead byte" );
            }
            m_code_point_ref = Cp_bytes_ref( tag::Unchecked(), it );
        }

        template< Step_delta::Enum delta >
        void step_()
        {
            if constexpr( delta == Step_delta::forward ) {
                step_forward();
            } else {
                step_backward();
            }
        }

        template< Step_delta::Enum delta >
        void skip_to_next_lead_bytes_( const int n_max_units = 42 )
        {
            Unit_iterator skipper = m_code_point_ref.unit_iterator();
            for( int i = 0; i < n_max_units; ++i ) {
                skipper += delta;
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
    };
    
    using Cp_iterator_core = Cp_iterator_core_<const char*>;

    template< class Basic_unit_iterator, bool check = true >
    class Cp_iterator_:
        public Cp_iterator_core_< Basic_unit_iterator, check >
    {
        // TODO: standard-iterator stuff.
    public:
        using Base = Cp_iterator_core_<Basic_unit_iterator, check>;
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
        class Basic_unit_iterator,
        class tp_It = Cp_iterator_< Basic_unit_iterator >
        >
    constexpr auto to_code_point_iterators( in_<Basic_unit_iterator> it_first, const int n )
        -> Iterator_pair_< tp_It >
    { return {tp_It( it_first ), tp_It( tag::Unchecked(), it_first + n )}; }

    constexpr auto to_code_point_iterators( in_<string_view> s )
        -> Iterator_pair_< Cp_iterator >
    { return to_code_point_iterators( s.data(), int_size_of( s ) ); }
        
    namespace x = u8;
    namespace exports { using
        x::Cp_iterator_core_,
        x::Cp_iterator_core,
        x::Cp_iterator_,
        x::Cp_iterator,
        x::to_code_point_iterators;
    }  // namespace exports
}  // fsm_definitions::u8

namespace fabulous_support_machinery{
    // `u8::` stuff is intentionally not available unqualified in fsm namespace.

    // Not a simple equate because may need to be an extension of earlier declared namespace.
    namespace u8{
        using namespace fsm_definitions::u8::exports;
    }  // namespace u8
}  // namespace fabulous_support_machinery
