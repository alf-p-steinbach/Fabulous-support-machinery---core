// By default FSM uses either (1) the C++ standard library's `fmt` functionality, or
// (2) the original `fmt` library as a header only library, i.e. with `FMT_HEADER_ONLY`
// defined, depending on the version of the C++ standard. You can define the
// preprocessor symbol `FSM_NO_FMT_HEADER_ONLY_PLEASE` to avoid the 2nd possibility.
//
#if 0
#   define  FSM_NO_FMT_HEADER_ONLY_PLEASE
#endif

// All the separately compiled source code of the FSM core + text-io libraries:
#include <fsm/text-io.implementation.cpp-include>
