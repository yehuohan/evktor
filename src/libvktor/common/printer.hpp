#pragma once

#if 0
    // Implement printer with cstdio
    #include <cstdio>

    #define vktOut(f, ...)                                        \
        do {                                                      \
            std::fprintf(stdout, "[vkt] " f "\n", ##__VA_ARGS__); \
            std::fflush(stdout);                                  \
        } while (0)
#endif

// Implement printer with fmt
#include <fmt/format.h>
#include <iostream>

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
