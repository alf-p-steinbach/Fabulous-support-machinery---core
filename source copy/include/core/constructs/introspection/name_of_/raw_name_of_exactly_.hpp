#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

// Using `raw_name_of_exactly_<T>()` instead of `typeid(T).name()` avoids decay of T.
//
// "Raw":
// The name returned is C++ implementation specific and can be mangled, e.g. for g++.
//
// "Exactly":
// Unfortunately `typeid` is unclean: if `Type` is cv-qualified, then `typeid(Type)`
// refers to a `std::type_info` object representing the cv-unqualified type.
// Additionally, if `Type` is a reference type, then `typeid(Type)` refers to a
// std::type_info object representing the cv-unqualified version (since C++11) of the
// referenced type, i.e. it ditches both reference and cv-qualification. Wrapping the
// type as a template parameter avoids these decays.

#include <string_view>

namespace fsm_definitions {
    using   std::string_view;

    template< class Type > struct Wrapped_ {};

    namespace introspection {
        template< class Type >
        auto raw_name_of_exactly_()
            -> string_view
        {
            const string_view   xname       = typeid( Wrapped_<Type> ).name();
            const size_t        i_first     = xname.find_first_of( '<' ) + 1;
            const size_t        i_beyond    = xname.find_last_of( '>' );

            return xname.substr( i_first, i_beyond - i_first );
        }
    }  // namespace introspection
}  // namespace fsm_definitions

namespace fsm {
    inline namespace introspection { using namespace fsm_definitions::introspection; }
}  // namespace fsm
