#pragma once
#include <cassert>
#include <cstdio>
#include <fmt/format.h>
#include <iostream>
#include <stdexcept>

#define NAMESPACE_BEGIN(x) namespace x {
#define NAMESPACE_END(x)   }

#if 0
    #define vktOut(f, ...)                                        \
        do {                                                      \
            std::fprintf(stdout, "[vkt] " f "\n", ##__VA_ARGS__); \
            std::fflush(stdout);                                  \
        } while (0)
#endif

#define vktFmt(f, ...) fmt::format(f, ##__VA_ARGS__)
#define vktOut(f, ...)                                                     \
    do {                                                                   \
        std::cout << vktFmt("[vkt] " f "\n", ##__VA_ARGS__) << std::flush; \
    } while (0)
#define vktLog(l, f, ...)                                                         \
    do {                                                                          \
        std::cout << vktFmt("[vkt][{}] " f "\n", l, ##__VA_ARGS__) << std::flush; \
    } while (0)

#define vktLogW(f, ...) vktLog("W", f, ##__VA_ARGS__)
// #define vktLogE(f, ...) vktLog("E", f, ##__VA_ARGS__)
#define vktLogE(f, ...)                                                                                  \
    do {                                                                                                 \
        std::cout << vktFmt("[vkt][E({}:{})] " f "\n", __FILE__, __LINE__, ##__VA_ARGS__) << std::flush; \
    } while (0)

#define vktErrorThrow(f, ...)  std::runtime_error(vktFmt(f, ##__VA_ARGS__))
#define vktErrorFormat(f, ...) vktErrorThrow(__FILE__ ":{}:0: error: " f, __LINE__, ##__VA_ARGS__)
/** Alias Er to Err<std::runtime_error> */
#define Er(f, ...) Err(vktErrorFormat(f, ##__VA_ARGS__))

/**
 * @brief Return Er on non-success Vulkan result
 *
 * 'r' must not be '__ret__'
 */
#define OnRet(r, f, ...)                                                              \
    {                                                                                 \
        VkResult __ret__ = (r);                                                       \
        if (__ret__ != VK_SUCCESS) {                                                  \
            return Er("[VkResult = {}] " f, VkStr(VkResult, __ret__), ##__VA_ARGS__); \
        }                                                                             \
    }

/** By pass Result<Err> */
#define OnErr(r)                     \
    if ((r).isErr()) {               \
        return Err((r).unwrapErr()); \
    }

/** Assert with message */
#define OnCheck(c, f, ...)                                                                                       \
    {                                                                                                            \
        if (!(c)) {                                                                                              \
            std::cout << vktFmt("[vkt][crash({}:{})] " f "\n", __FILE__, __LINE__, ##__VA_ARGS__) << std::flush; \
            assert(c);                                                                                           \
        }                                                                                                        \
    }
