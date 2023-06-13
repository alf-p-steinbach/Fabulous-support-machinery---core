#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <mutex>

namespace fabulous_support_machinery {
    
    using Mutex_locker = std::unique_lock<std::mutex>;

}  // namespace fabulous_support_machinery
