#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <stdexcept>
namespace fsm_definitions {
    namespace exception { inline namespace types {
        class Unknown_exception:
            public Std_exception
        {
            exception_ptr   m_ptr;

        public:
            Unknown_exception( in_<exception_ptr> p ): m_ptr( p ) {}
            auto ptr() const -> exception_ptr { return m_ptr; }
            auto what() const noexcept -> const char* override { return "<unknown exception>"; }
        };
    } }  // namespace exceptions / inline namespace types
}  // namespace fsm_definitions

namespace fsm {
    inline namespace exception { using namespace fsm_definitions::exception; }
}  // namespace fsm
