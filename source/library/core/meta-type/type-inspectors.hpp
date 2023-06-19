#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/types/fundamental/byte-types/Byte.hpp>                     // bits_per_byte

#include <type_traits>

namespace fabulous_support_machinery {
    template< class T >
    constexpr int   n_bytes_per_                = static_cast<int>( sizeof( T ) );

    template< class T >
    constexpr int   bits_per_                   = n_bytes_per_<T>*bits_per_byte;

    template< class A, class B >    
    constexpr bool  is_same_                    = std::is_same_v<A, B>;

    template< class Base, class Derived >    
    constexpr bool  are_base_and_derived_       = std::is_base_of_v<Base, Derived>;

    template< class To, class From >
    constexpr bool  converts_to_                = std::is_convertible_v<From, To>;

    // Like C++20 concept `derived_from`
    template< class Base, class Derived >
    constexpr bool  type_is_a_                  =
        are_base_and_derived_< Base, Derived > and
        converts_to_< const volatile Base*, const volatile Derived* >;

    template< class T, class Arg >
    constexpr auto object_is_a_( const Arg& o )
        -> bool
    { return (dynamic_cast<const volatile T*>( &o ) != nullptr); }


    // Unwrappers.

    template< class E >     using Integer_type_of_      = std::underlying_type_t< E >;
    
    template< class T >     using Unconst_              = std::remove_const_t<T>;
    template< class T >     using Unvolatile_           = std::remove_volatile_t<T>;
    template< class T >     using Uncv_                 = std::remove_cv_t<T>;
    
    template< class T>      using Unref_                = std::remove_reference_t<T>;
    template< class T>      using Unptr_                = std::remove_pointer_t<T>;
    
    template< class T>      using Bare_                 = Uncv_<Unref_<T>>;


    // Built-in type detectors for foundation functionality.

    template< class T >
    constexpr bool  is_builtin_integral_type_   = std::is_integral_v<T>;

    template< class T >
    constexpr bool  is_builtin_integer_         = is_builtin_integral_type_<T> and not is_same_<T, bool>;

    template< class T >
    constexpr bool  is_builtin_signed_          = std::is_signed_v<T>;
    
    template< class T >
    constexpr bool  is_builtin_signed_integer_  = is_builtin_integer_<T> and is_builtin_signed_<T>;
    
    template< class T >
    constexpr bool  is_builtin_unsigned_        = std::is_unsigned_v<T>;
    
    template< class T >
    constexpr bool  is_builtin_unsigned_integer_ = is_builtin_integer_<T> and is_builtin_unsigned_<T>;
    

    // Numerical type classifiers.
    // std::is_signed etc. can't be specialized for user defined types, formal UB.
    // The following `Is_integer_` and `Is_signed_` can be specialized.

    template< class T >
    struct Is_integer_{ static inline constexpr bool yes = is_builtin_integer_<T>; };
    
    template< class T >
    struct Is_signed_{ static inline constexpr bool yes = is_builtin_signed_<T>; };
    
    template< class T >
    constexpr bool is_integer_                  = Is_integer_<T>::yes;
    
    template< class T > 
    constexpr bool is_signed_                   = Is_signed_<T>::yes;
    
    template< class T >     
    constexpr bool is_signed_integer_           = is_integer_<T> and is_signed_<T>;
    
    template< class T > 
    constexpr bool is_unsigned_                 = not is_signed_<T>;
    
    template< class T >     
    constexpr bool is_unsigned_integer_         = is_integer_<T> and is_unsigned_<T>;

}  // namespace fabulous_support_machinery
