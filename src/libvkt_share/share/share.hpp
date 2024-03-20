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

#define LogW(f, ...) vktLog("W", f, ##__VA_ARGS__)
// #define LogE(f, ...) vktLog("E", f, ##__VA_ARGS__)
#define LogE(f, ...)                                                                                     \
    do {                                                                                                 \
        std::cout << vktFmt("[vkt][E({}:{})] " f "\n", __FILE__, __LINE__, ##__VA_ARGS__) << std::flush; \
    } while (0)

#define ErrorThrow(f, ...)  std::runtime_error(vktFmt(f, ##__VA_ARGS__))
#define ErrorFormat(f, ...) ErrorThrow(__FILE__ ":{}:0: error: " f, __LINE__, ##__VA_ARGS__)
#define Er(f, ...)          Err(ErrorFormat(f, ##__VA_ARGS__))

/** Assert with message */
#define Check(c, f, ...)                                                                                         \
    {                                                                                                            \
        if (!(c)) {                                                                                              \
            std::cout << vktFmt("[vkt][crash({}:{})] " f "\n", __FILE__, __LINE__, ##__VA_ARGS__) << std::flush; \
            assert(c);                                                                                           \
        }                                                                                                        \
    }

/** By pass Result<Err> */
#define OnErr(r)                     \
    if ((r).isErr()) {               \
        return Err((r).unwrapErr()); \
    }
