#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/declarations/type_builders.hpp>   // in_
#include <fsm/core/exports/constructs/declarations/FSM_ENABLE_IF.hpp>   // FSM_ENABLE_IF
#include <fsm/core/exports/meta-type/type-inspectors.hpp>               // type_is_a_
#include <fsm/core/exports/mixins/Relational_operators_mixin_.hpp>      // Relational_operators_mixin_

namespace fabulous_support_machinery::_definitions {
    // enum class Input_stream_id { in = 0 };
    // enum class Output_stream_id { out = 1, err = 2 };
    // enum class Stream_id extends Input_stream_id, Output_stream_id {};

    class Enumeration
    {
        const int   m_value;
        
    protected:
        constexpr Enumeration( const int value ): m_value( value ) {}
        
    public:
        constexpr operator int() const { return m_value; }  // Supports e.g. use in `switch`.
    };

    template< class E, FSM_ENABLE_IF( type_is_a_<Enumeration, E> ) >
    constexpr auto compare( const E a, const E b )
        -> int
    { return (+a - +b); }

    class Input_stream_id;
    struct Input_stream_id_names
    {
        static const Input_stream_id in;            // 0
    };

    class Input_stream_id:
        public Enumeration,
        public Relational_operators_mixin_<Input_stream_id>,
        public Input_stream_id_names
    {
    public:
        explicit constexpr Input_stream_id( const int value ): Enumeration( value ) {}
    };
    
    class Output_stream_id;
    struct Output_stream_id_names
    {
        static const Output_stream_id out;          // 1
        static const Output_stream_id err;          // 2
    };

    class Output_stream_id:
        public Enumeration,
        public Relational_operators_mixin_<Output_stream_id>,
        public Output_stream_id_names
    {
    public:
        explicit constexpr Output_stream_id( const int value ): Enumeration( value ) {}
    };

    class Stream_id:
        public Enumeration,
        public Relational_operators_mixin_<Stream_id>,
        public Input_stream_id_names,
        public Output_stream_id_names
    {
    public:
        explicit constexpr Stream_id( const int value ): Enumeration( value ) {}

        constexpr Stream_id( const Input_stream_id value ): Enumeration( +value ) {}
        constexpr Stream_id( const Output_stream_id value ): Enumeration( +value ) {}
    };

    // `inline` is necessary for Visual C++ 2022, even though it’s implied by `constexpr`.
    inline constexpr    Input_stream_id    Input_stream_id_names::in        { 0 };
    inline constexpr    Output_stream_id   Output_stream_id_names::out      { 1 };
    inline constexpr    Output_stream_id   Output_stream_id_names::err      { 2 };

    namespace d = _definitions;
    namespace exports{ using
        d::Input_stream_id,
        d::Output_stream_id,
        d::Stream_id;
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery { using namespace _definitions::exports; }
