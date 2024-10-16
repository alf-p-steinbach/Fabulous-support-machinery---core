#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/std_core_language.hpp>

#include <fsm/core/basic_type/bit_operations/bits_per_.hpp>
#include <fsm/core/exception_handling/FSM_FAIL.hpp>
#include <fsm/core/parameter_passing/enabled_if_.hpp>

#include <string_view>
#include <type_traits>

namespace fsm_definitions {
    using   fsm::bits_per_,                 // basic_types/bits_per_.hpp
            fsm::now,                       // exception_handling/$fail.hpp
            fsm::enabled_if_;               // parameter_passing/enabled_if_.hpp
    using   std::string_view,               // <string_view>
            std::is_unsigned_v;             // <type_traits>

    namespace basic_types {
        template< class Uint, bool = enabled_if_< is_unsigned_v< Uint > > >
        class Bitpattern_
        {
            Uint        m_mask      = 0;
            Uint        m_value     = 0;

        public:
            struct Spec{ enum Enum: char { zero = '0', one = '1', any = '*', separator = '\'' }; };

            Bitpattern_( in_<string_view> spec )
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
                        }
                        case Spec::separator: {}
                        default: {
                            $fail( "Invalid character in bitpattern spec" );
                        }
                    }
                }
            }
        };
    }  // namespace basic_types
}  // namespace fsm_definitions

namespace fsm {
    inline namespace basic_types{ using namespace fsm_definitions::basic_types; }
}  // namespace fsm
