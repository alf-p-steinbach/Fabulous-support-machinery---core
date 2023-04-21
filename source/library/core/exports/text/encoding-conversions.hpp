#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/failure/detecting/FSM_STATIC_ASSERT.hpp>
#include <fsm/core/exports/constructs/declarations/type_builders.hpp>
#include <fsm/core/exports/meta-type/type-inspectors/compiletime-type-inspectors.hpp>  // bits_per_

#include <fsm/core/exports/text/encoding/u8/Code_point_iterator_.hpp>

#include <array>        // std::array
#include <string>       // std::wstring
#include <string_view>  // std::string_view
#include <type_traits>  // std::remove_reference_t
#include <utility>      // std::move

#include <assert.h>


namespace fabulous_support_machinery::text {
    namespace fsm       = fabulous_support_machinery;
    using   fsm::const_, fsm::in_, fsm::Byte;
    using   std::basic_string, std::wstring, std::u16string,
            std::string_view,
            std::remove_reference_t,
            std::move;

    template< class U_string >
    inline auto to_utf_16_as_( in_<string_view> s, U_string&& buffer = {} )
        -> U_string
    {
        using Unit = remove_reference_t<decltype( buffer[0] )>;
        FSM_STATIC_ASSERT( bits_per_<Unit> == 16 );
        buffer.clear();  buffer.reserve( s.size() );
        
        for( const u8::Code_point_ref seq: u8::to_code_point_iterators( s ) ) {
            // TODO: surrogate pairs
            buffer.push_back( static_cast<Unit>( seq.cp_number() ) );
        }

        return buffer;
    }

    template< class U_string >
    inline auto to_( in_<string_view> s, U_string&& buffer = {} )
        -> U_string;

    template<>
    inline auto to_<wstring>( in_<string_view> s, wstring&& buffer )
        -> wstring
    {
        if constexpr( bits_per_<wchar_t> == 16 ) {
            return to_utf_16_as_<wstring>( s, move( buffer ) );
        } else if constexpr( bits_per_<wchar_t> == 32 ) {
            throw "to 32-bit wchar_t-string not supported.";
        } else {
            throw "Gah!";
        }
        for( ;; ) {}        // Should never get here.
    }

    template<>
    inline auto to_<u16string>( in_<string_view> s, u16string&& buffer )
        -> u16string
    { return to_utf_16_as_<u16string>( s, move( buffer ) ); }
}  // namespace fabulous_support_machinery::text
