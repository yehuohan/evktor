#pragma once

#if 0
    // Implement printer with cstdio
    #include <cstdio>

    #ifndef VKT_PRINTER
        #define VKT_PRINTER stdout
    #endif

    #define vktOut(f, ...)                                             \
        do {                                                           \
            std::fprintf(VKT_PRINTER, "[vkt] " f "\n", ##__VA_ARGS__); \
            std::fflush(VKT_PRINTER);                                  \
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

#define LogE(f, ...) vktLog("E", f, ##__VA_ARGS__)
#define LogW(f, ...) vktLog("W", f, ##__VA_ARGS__)
