#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <fsm/core/constructs/introspection/name_of_/unmangled_and_cleaned_type_name_from.hpp>

#include <string>
#include <string_view>

// Unfortunately `typeid` is unclean: if `Type` is cv-qualified, then `typeid(Type)`
// refers to a `std::type_info` object representing the cv-unqualified type.
// Additionally, if `Type` is a reference type, then `typeid(Type)` refers to a
// std::type_info object representing the cv-unqualified version (since C++11) of the
// referenced type, i.e. it ditches both reference and cv-qualification. Wrapping the
// type as a template parameter avoids these decays.

namespace fsm_definitions {
    using   fsm::unmangled_and_cleaned_type_name_from;
    using   std::string,
            std::string_view;

    template< class Type > struct Wrapped_ {};

    namespace introspection {

        template< class Type >
        auto name_of_()
            -> std::string
        {
            const string_view   raw_wrapped_name    = typeid( Wrapped_<Type> ).name();
            const string        wrapped_name        = unmangled_and_cleaned_type_name_from( raw_wrapped_name );

            const size_t        i_first     = wrapped_name.find_first_of( '<' ) + 1;
            const size_t        i_beyond    = wrapped_name.find_last_of( '>' );

            return wrapped_name.substr( i_first, i_beyond - i_first );
        }

    }  // namespace introspection
}  // namespace fsm_definitions

namespace fsm {
    inline namespace introspection { using namespace fsm_definitions::introspection; }
}  // namespace fsm
