#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/basic-types/byte-types/byte-info.hpp>        // bits_per_byte
#include <fsm/core/exports/meta-type/class-kinds/Non_instantiable.hpp>  // Non_instantiable

#include <type_traits>
#include <tuple>

namespace fabulous_support_machinery::_definitions {
    using   std::is_same_v,
            std::tuple_element_t, std::tuple;

    template< class... Types > struct Typelist_;


    // Head:
    
    template< class Types >
    struct Typelist_head_t_;

    template< class Types >
    using Typelist_head_ = typename Typelist_head_t_<Types>::T;

    template< class Type >
    struct Typelist_head_t_<Typelist_<Type>>
    {
        using T = Type;
    };

    template< class First, class... Rest >
    struct Typelist_head_t_<Typelist_<First, Rest...>>
    {
        using T = First;
    };
    

    // Tail:
    
    template< class Types >
    struct Typelist_tail_t_;

    template< class Types >
    using Typelist_tail_ = typename Typelist_tail_t_<Types>::Result_typelist;
    
    template< class First, class... Rest >
    struct Typelist_tail_t_<Typelist_<First, Rest...>>
    {
        using Result_typelist = Typelist_<Rest...>;
    };


    // Typelist_:
    
    template< class... Types >
    struct Typelist_: Non_instantiable
    {
        using Self = Typelist_;
        static constexpr int count = sizeof...( Types );

        template< int i >
        using at_ = tuple_element_t<i, tuple<Types...>>;
        
        using Head = Typelist_head_<Self>;              // A type
        using Tail = Typelist_tail_<Self>;              // A Typelist_<...>
        
        template< class T >
        static constexpr bool contains_         = (is_same_v<T, Types> or ...);
        
        template< class T >
        static constexpr bool all_types_are_    = (is_same_v<T, Types> and ...);
    };

    template<>
    struct Typelist_<>: Non_instantiable
    {
        using Self = Typelist_;
        static constexpr int count = 0;

        // No `Head` or `Tail`.
    
        template< class T >
        static constexpr bool contains_         = false;
        
        template< class T >
        static constexpr bool all_types_are_    = true;
    };


    // Joined:

    template< class... Typelists >
    struct Joined_t_;

    template< class... Typelists >
    using Joined_ = typename Joined_t_<Typelists...>::Result_typelist;

    template<>
    struct Joined_t_<>
    {
        using Result_typelist = Typelist_<>;
    };
    
    template< class... Types >
    struct Joined_t_<Typelist_<Types...>>
    {
        using Result_typelist = Typelist_<Types...>;
    };
    
    template< class... Types_a, class... Types_b >
    struct Joined_t_<Typelist_<Types_a...>, Typelist_<Types_b...>>
    {
        using Result_typelist = Typelist_<Types_a..., Types_b...>;
    };

    template< class... Types_a, class... Types_b, class... More_typelists >
    struct Joined_t_<Typelist_<Types_a...>, Typelist_<Types_b...>, More_typelists...>
    {
        using Result_typelist = Joined_<
            Joined_<Typelist_<Types_a...>, Typelist_<Types_b...>>,
            More_typelists...
            >;
    };


    namespace d = _definitions;
    namespace exports { using
        d::Typelist_,
        d::Joined_;
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery { using namespace _definitions::exports; }
