#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/exports/+std-cpp-language.hpp>

#include <fsm/core/exports/support-for-collections/FSM_ITS_RANGE.hpp>
#define $its_range      FSM_ITS_RANGE

#include <fsm/core/exports/constructs/declarations/FSM_NSNAME_FROM.hpp>
#define $nsname_from    FSM_NSNAME_FROM

#include <fsm/core/exports/constructs/declarations/FSM_TYPE_OF.hpp>
#define $type_of        FSM_TYPE_OF

#include <fsm/core/exports/constructs/declarations/FSM_WITH.hpp>
#define $with           FSM_WITH
#define $with_mutable   FSM_WITH_MUTABLE

#include <fsm/core/exports/constructs/declarations/FSM_ENABLE_IF_.hpp>
#define $enable_if_     FSM_ENABLE_IF_

#include <fsm/core/exports/failure/expressing/FSM_FAIL.hpp>
#define $fail           FSM_FAIL
#define $fail_          FSM_FAIL_

#include <fsm/core/exports/failure/detecting/FSM_EXPECT.hpp>
#define $expect         FSM_EXPECT

#include <fsm/core/exports/failure/detecting/FSM_STATIC_ASSERT.hpp>
#define $static_assert  FSM_STATIC_ASSERT

#include <fsm/core/exports/constructs/flow-control/FSM_IF.hpp>
#define $if_with        FSM_IF_WITH
#define $if             FSM_IF

#include <fsm/core/exports/+std-cpp-language/versions.hpp>
#define $cpp_version    FSM_CPP_VERSION
#define $cpp98          FSM_CPP98
#define $cpp03          FSM_CPP03
#define $cpp11          FSM_CPP11
#define $cpp14          FSM_CPP14
#define $cpp17          FSM_CPP17
#define $cpp20          FSM_CPP20
