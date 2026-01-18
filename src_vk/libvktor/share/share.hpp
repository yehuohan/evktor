#pragma once
#include "helpers.hpp"
#include <cassert>
#include <fmt/format.h>
#include <stdexcept>

#define NAMESPACE_BEGIN(x) namespace x {
#define NAMESPACE_END(x)   }

/** Formatting function with {} style */
#define vktFmt(f, ...) fmt::format(f, ##__VA_ARGS__)

#define vktOut(f, ...)    vkt::print(vktFmt("[vkt] " f "\n", ##__VA_ARGS__))
#define vktLog(l, f, ...) vkt::print(vktFmt("[vkt][{}] " f, l, ##__VA_ARGS__))

#define vktLogD(f, ...) vktLog("D", f "\n", ##__VA_ARGS__)
#define vktLogW(f, ...) vktLog("W", f "\n", ##__VA_ARGS__)
// #define vktLogE(f, ...) vktLog("E", f "\n", ##__VA_ARGS__)
#define vktLogE(f, ...) vkt::print(vktFmt("[vkt][E({}:{})] " f "\n", __FILE__, __LINE__, ##__VA_ARGS__))

#define vktErrThrow(f, ...) std::runtime_error(vktFmt(f, ##__VA_ARGS__))
#define vktErr(f, ...)      vktErrThrow(__FILE__ ":{}:0: error: " f, __LINE__, ##__VA_ARGS__)
/** Alias Er to Err<std::runtime_error> */
#define Er(f, ...) Err(vktErr(f, ##__VA_ARGS__))

/**
 * @brief Return Er on non-success Vulkan result
 *
 * 'r' must not be '__res__'
 */
#define OnRet(r, f, ...)                                                              \
    {                                                                                 \
        VkResult __res__ = (r);                                                       \
        if (__res__ != VK_SUCCESS) {                                                  \
            return Er("[VkResult = {}] " f, VkStr(VkResult, __res__), ##__VA_ARGS__); \
        }                                                                             \
    }

/**
 * @brief By pass Result<Err>
 *
 * 'r' must not be '__res__'
 */
#define OnErr(r)                             \
    {                                        \
        auto& __res__ = (r);                 \
        if (__res__.isErr()) {               \
            return Err(__res__.unwrapErr()); \
        }                                    \
    }

/** Assert with message */
#define OnCheck(c, f, ...)                                                                        \
    {                                                                                             \
        if (!(c)) {                                                                               \
            vkt::print(vktFmt("[vkt][crash({}:{})] " f "\n", __FILE__, __LINE__, ##__VA_ARGS__)); \
            assert(0);                                                                            \
        }                                                                                         \
    }

NAMESPACE_BEGIN(vkt)

void print(const String& str);

NAMESPACE_END(vkt)
