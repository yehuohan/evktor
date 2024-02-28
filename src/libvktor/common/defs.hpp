#pragma once
#include "printer.hpp"
#include <cassert>
#include <stdexcept>

#define NAMESPACE_BEGIN(x) namespace x {
#define NAMESPACE_END(x)   }

#define ErrorThrow(f, ...)  std::runtime_error(vktFmt(f, ##__VA_ARGS__))
#define ErrorFormat(f, ...) ErrorThrow(__FILE__ ":{}:0: error: " f, __LINE__, ##__VA_ARGS__)
#define Er(f, ...)          Err(ErrorFormat(f, ##__VA_ARGS__))

#define Check(c, f, ...)                                                                                         \
    {                                                                                                            \
        if (!(c)) {                                                                                              \
            std::cout << vktFmt("[vkt][crash({}:{})] " f "\n", __FILE__, __LINE__, ##__VA_ARGS__) << std::flush; \
            assert(c);                                                                                           \
        }                                                                                                        \
    }
