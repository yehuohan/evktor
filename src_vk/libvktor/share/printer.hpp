#pragma once
#include "helpers/helpers.hpp"
#include <cassert>
#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <source_location>
#include <stdexcept>

enum class FmtLevel {
    N = 'N', // None
    V = 'V', // Verbose
    I = 'I', // Info
    D = 'D', // Debug
    W = 'W', // Warning
    E = 'E', // Error
};

/**
 * @brief Write string to log file only for fmtPrint
 */
void fmtWrite(const String& str);

/**
 * @brief Print with color, time, tag and level
 */
template <const char* Tag, typename... Args>
void fmtPrint(FmtLevel level, const std::source_location& loc, fmt::format_string<Args...> fmt, Args&&... args) {
    auto time_str = fmt::format("{:%m-%d %T}", fmt::localtime(std::time(nullptr)));

    std::string level_str = fmt::format("[{}]", static_cast<char>(level));
    fmt::text_style style = fg(fmt::color::white);
    switch (level) {
    case FmtLevel::N: level_str = ""; break;
    case FmtLevel::W: style = fg(fmt::color::yellow); break;
    case FmtLevel::E:
        style = fg(fmt::color::red);
        level_str = fmt::format("[E({}:{})]", loc.file_name(), loc.line());
        break;
    default: break;
    }

    auto str = fmt::format("[{}][{}]{} {}", time_str, Tag, level_str, fmt::format(fmt, std::forward<Args>(args)...));
    fmt::print(style, "{}\n", str);

#ifdef VKT_SHARE_PRINT2FILE
    fmtWrite(str);
#endif
}

inline constexpr char VKTOR_TAG[] = "vkt";

/** Formatting function with {} style */
#define vktFmt(f, ...) fmt::format(f, ##__VA_ARGS__)

#define vktOut(f, ...)    fmtPrint<VKTOR_TAG>(FmtLevel::N, std::source_location::current(), f, ##__VA_ARGS__)
#define vktLog(l, f, ...) fmtPrint<VKTOR_TAG>(l, std::source_location::current(), f, ##__VA_ARGS__)
#define vktLogD(f, ...)   vktLog(FmtLevel::D, f, ##__VA_ARGS__)
#define vktLogW(f, ...)   vktLog(FmtLevel::W, f, ##__VA_ARGS__)
#define vktLogE(f, ...)   vktLog(FmtLevel::E, f, ##__VA_ARGS__)

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
#define OnCheck(c, f, ...)             \
    {                                  \
        if (!(c)) {                    \
            vktLogE(f, ##__VA_ARGS__); \
            assert(0);                 \
        }                              \
    }
