#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/misc/support-for-collections/FSM_ITS_RANGE.hpp>
#define $its_range                  FSM_ITS_RANGE

#include <fsm/core/constructs/declarations/FSM_ENABLE_IF.hpp>
#define $enable_if                  FSM_ENABLE_IF

#include <fsm/core/constructs/declarations/FSM_NOT_USING.hpp>
#define $not_using                  FSM_NOT_USING

#include <fsm/core/constructs/declarations/FSM_NS_FROM.hpp>
#define $ns_from                    FSM_NS_FROM

#include <fsm/core/constructs/declarations/FSM_TYPE_OF.hpp>
#define $type_of                    FSM_TYPE_OF

#include <fsm/core/constructs/declarations/FSM_WITH.hpp>
#define $with                       FSM_WITH
#define $with_mutable               FSM_WITH_MUTABLE

#include <fsm/core/constructs/introspection/FSM_FUNCTION_NAME.hpp>
#define $function_name              FSM_FUNCTION_NAME

#include <fsm/core/failure/expressing/FSM_FAIL.hpp>
#define $failure_message            FSM_FAILURE_MESSAGE
#define $fail_with_args_            FSM_FAIL_WITH_ARGS_
#define $fail_                      FSM_FAIL_
#define $fail_with_default_message_ FSM_FAIL_WITH_DEFAULT_MESSAGE_
#define $fail                       FSM_FAIL

#include <fsm/core/failure/detecting/FSM_EXPECT.hpp>
#define $expect                     FSM_EXPECT

#include <fsm/core/failure/detecting/FSM_STATIC_ASSERT.hpp>
#define $static_assert              FSM_STATIC_ASSERT

#include <fsm/core/constructs/flow-control/FSM_IF.hpp>
#define $if_with                    FSM_IF_WITH
#define $if                         FSM_IF

#include <fsm/core/+std-cpp-language/versions.hpp>
#define $cpp_version                FSM_CPP_VERSION
#define $cpp98                      FSM_CPP98
#define $cpp03                      FSM_CPP03
#define $cpp11                      FSM_CPP11
#define $cpp14                      FSM_CPP14
#define $cpp17                      FSM_CPP17
#define $cpp20                      FSM_CPP20
