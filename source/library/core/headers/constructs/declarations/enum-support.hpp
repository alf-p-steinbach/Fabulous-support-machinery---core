#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/headers/+std-cpp-language.hpp>

namespace fabulous_support_machinery {
    
    template< class Enum_or_wrapper >
    constexpr auto n_enumerators_of_ = static_cast<int>( Enum_or_wrapper::_ );

    // TODO: declaration helper macro

}  // namespace fabulous_support_machinery
