// https://fmt.dev/11.0/api/#formatting-user-defined-types

#if 0
template <> struct fmt::formatter<color>: formatter<string_view> {
  // parse is inherited from formatter<string_view>.

  auto format(color c, format_context& ctx) const
    -> format_context::iterator;
};

// color.cc:
#include "color.h"
#include <fmt/format.h>

auto fmt::formatter<color>::format(color c, format_context& ctx) const
    -> format_context::iterator {
  string_view name = "unknown";
  switch (c) {
  case color::red:   name = "red"; break;
  case color::green: name = "green"; break;
  case color::blue:  name = "blue"; break;
  }
  return formatter<string_view>::format(name, ctx);
}
#endif
