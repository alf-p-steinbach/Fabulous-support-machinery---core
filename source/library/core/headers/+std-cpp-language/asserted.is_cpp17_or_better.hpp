#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include "versions.hpp"
#if FSM_CPP_VERSION < FSM_CPP17
#   error "C++17 or better is required (e.g. Visual C++ options '/std:c++17 /Zc:__cplusplus')."
#   include <stop-compilation>
#endif
