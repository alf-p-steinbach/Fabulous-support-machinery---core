﻿#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/constructs/type_builders.hpp> // in_value_

#include <chrono>

namespace fabulous_support_machinery{

    using   Duration = std::chrono::duration<double>;   // Unit is seconds by default.

}  // namespace fabulous_support_machinery
