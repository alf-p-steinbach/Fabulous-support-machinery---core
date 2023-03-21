Simple build of an example:

• If you're using C++17 or earlier, install the fmt library.
• Include this folder's “fabulous_support_machinery.cpp” in the build.

You can install the fmt library from <url: https://github.com/fmtlib/fmt>.

The fmt library is however not needed for all examples, e.g. it's not needed for the examples in the “hello” folder. You can try out those examples without installing fmt. Also, you don't need to install fmt if you're using a full C++20 or later, because FSM uses the standard library's adoption of the relevant parts of the fmt library if that's available.

---

FSM uses an as yet still rare model of simple /single file build/ for a simple library.

Compiling the examples folder's “fabulous_support_machinery.cpp” file builds the whole FSM library, because the file `#include`s all of the FSM library's separately compiled code for this system and compiler.

You can make your own such file by `#include`-ing the implementation source aggregation file `<fabulous_support_machinery/_impl.core.cpp-include>`.

---

Define `FSM_USE_ORIGINAL_FMTLIB_PLEASE` to force use of the original fmt library instead of the standard library.

Define `FMT_HEADER_ONLY` to use the fmt library as header only (this implies `FSM_USE_ORIGINAL_FMTLIB_PLEASE`).
