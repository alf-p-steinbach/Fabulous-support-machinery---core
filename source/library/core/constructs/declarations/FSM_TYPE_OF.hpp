﻿#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/meta-type/type-inspectors.hpp>   // Bare_

#define FSM_TYPE_OF( o )    ::fabulous_support_machinery::Bare_<decltype( o )>