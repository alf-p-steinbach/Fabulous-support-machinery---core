#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/basic_type/bit_operations/bits_per_.hpp>
#include <fsm/core/basic_type/names/C_str.hpp>
#include <fsm/core/exception_handling/FSM_FAIL.hpp>
#include <fsm/core/parameter_passing/enabled_if_.hpp>

#include <string>
#include <string_view>
#include <type_traits>

namespace fsm_definitions {
    using   fsm::bits_per_,                 // basic_type/bit_operations/bits_per_.hpp
            fsm::C_str,                     // basic_type/C_Str
            fsm::now,                       // exception_handling/FSM_FAIL.hpp
            fsm::enabled_if_;               // parameter_passing/enabled_if_.hpp
    using   std::string,                    // <string>
            std::string_view,               // <string_view>
            std::is_unsigned_v;             // <type_traits>

    namespace basic_type { inline namespace bit_operations{
        template< class Uint, bool = enabled_if_< is_unsigned_v< Uint > >() >
        class Bitpattern_
        {
            Uint        m_mask      = 0;
            Uint        m_value     = 0;

            auto str( const bool do_group_digits ) const
                -> string
            {
                string result;
                for( int i = bits_per_<Uint> - 1; i >= 0;  --i ) {
                    const unsigned mask_bit     = (m_mask >> i) & 1;
                    const unsigned value_bit    = (m_value >> i) & 1;
                    result += (mask_bit? char( value_bit + '0' ) : char( Spec::any ));
                    if( do_group_digits and i > 0 and i % 4 == 0 ) {
                        result += char( Spec::separator );
                    }
                }
                return result;
            }

        public:
            struct Spec{ enum Enum: char { zero = '0', one = '1', any = 'x', separator = '\'' }; };
            constexpr Bitpattern_( in_<string_view> spec )
            {
                int n_bitspecs = 0;
                for( const char ch: spec ) {
                    switch( ch ) {
                        case '0':  case '1': case Spec::any: {
                            now( n_bitspecs < bits_per_<Uint> )
                                or $fail( "Too many bits in the specification." );
                            m_mask <<= 1u;  m_value <<= 1u;
                            if( ch != Spec::any ) {
                                m_mask |= 1u;
                                m_value |= (ch - '0');
                            }
                            ++n_bitspecs;
                            break;
                        }
                        case Spec::separator: { break; }
                        default: {
                            $fail( "Invalid character in bitpattern spec." );
                            for( ;; ) {}    // Should never get here.
                        }
                    }
                }
            }

            template< class Arg >
            constexpr auto matches( Arg ) const noexcept -> bool = delete;
            
            constexpr auto matches( const Uint bits ) const noexcept
                -> bool
            { return ((bits & m_mask) == m_value); }

            constexpr auto varying_bits_of( const Uint bits ) const noexcept
                -> Uint
            { return bits & ~m_mask; }

            constexpr auto n_masked_bits() const noexcept
                -> Uint
            {
                Uint count = 0;
                for( Uint bits = m_mask; bits != 0; bits >>= 1 ) {
                    count += !!(bits & 1);
                }
                return count;
            }

            constexpr auto n_varying_bits() const noexcept
                -> Uint
            { return bits_per_<Uint> - n_masked_bits(); }

            auto str() const                -> string { return str( false ); }
            auto str_with_groups() const    -> string { return str( true ); }
        };

        constexpr auto operator""_bp( const C_str spec, const size_t spec_length )
            -> Bitpattern_<unsigned>
        { return Bitpattern_<unsigned>( string_view( spec, spec_length ) ); }

    } }  // namespace basic_type, inline namespace bit_operations
}  // namespace fsm_definitions

namespace fsm {
    inline namespace basic_type{ using namespace fsm_definitions::basic_type; }
}  // namespace fsm
