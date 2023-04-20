#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/type_builders.hpp>                  // in_

namespace fabulous_support_machinery::_definitions {
    // enum class Input_stream_id{ in = 0 };
    // enum class Output_stream_id{ out = 1, err = 2 };
    // enum class Stream_id: extends Input_stream_id, Output_stream_id {};

    class Input_stream_id;
    struct Input_stream_id_names
    {
        static const Input_stream_id in;            // 0
    };

    class Output_stream_id;
    struct Output_stream_id_names
    {
        static const Output_stream_id out;          // 1
        static const Output_stream_id err;          // 2
    };

    class Input_stream_id:
        public Input_stream_id_names
    {
        const int   m_value;
    
    public:
        explicit constexpr Input_stream_id( const int value ): m_value( value ) {}
        constexpr auto operator+() const -> int { return m_value; }
    };
    
    class Output_stream_id:
        public Output_stream_id_names
    {
        const int   m_value;

    public:
        explicit constexpr Output_stream_id( const int value ): m_value( value ) {}
        constexpr auto operator +() const -> int { return m_value; }
    };

    class Stream_id:
        public Input_stream_id_names,
        public Output_stream_id_names
    {
        const int   m_value;

    public:
        explicit constexpr Stream_id( const int value ): m_value( value ) {}

        constexpr Stream_id( const Input_stream_id value ): m_value( +value ) {}
        constexpr Stream_id( const Output_stream_id value ): m_value( +value ) {}
        constexpr auto operator +() const -> int { return m_value; }
    };

    // `inline` is necessary for Visual C++ 2022, even though it’s implied by `constexpr`.
    inline constexpr    Input_stream_id    Input_stream_id_names::in   = Input_stream_id( 0 );
    inline constexpr    Output_stream_id   Output_stream_id_names::out = Output_stream_id( 1 );
    inline constexpr    Output_stream_id   Output_stream_id_names::err = Output_stream_id( 2 );
    
    namespace d = _definitions;
    namespace exports{ using
        d::Input_stream_id,
        d::Output_stream_id,
        d::Stream_id;
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery { using namespace _definitions::exports; }
