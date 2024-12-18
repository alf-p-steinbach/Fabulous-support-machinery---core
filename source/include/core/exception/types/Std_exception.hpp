#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/platform/std_core_language.hpp>

#include <stdexcept>
namespace fsm_definitions {
    namespace exception {
        using Std_exception = std::exception;   // <stdexcept>
    }
}  // namespace fsm_definitions

namespace fsm {
    inline namespace exception { using namespace fsm_definitions::exception; }
}  // namespace fsm
