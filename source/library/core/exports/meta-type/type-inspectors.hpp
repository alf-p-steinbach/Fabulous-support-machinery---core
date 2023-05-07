#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/basic-types/byte-types/byte-info.hpp> // bits_per_byte

#include <type_traits>

namespace fabulous_support_machinery {
    template< class T >
    constexpr int n_bytes_per_                  = static_cast<int>( sizeof( T ) );

    template< class T >
    constexpr int bits_per_                     = n_bytes_per_<T>*bits_per_byte;
    
    template< class A, class B >    
    constexpr bool  is_same_                    = std::is_same_v<A, B>;

    template< class D, class B >    
    constexpr bool  are_derived_and_base_       = std::is_base_of_v<B, D>;  // (sic!)


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
