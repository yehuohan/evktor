#pragma once

#if 0

    // Implement printer with cstdio
    #include <cstdio>

    #ifndef VKT_PRINTER
        #define VKT_PRINTER stdout
    #endif

    #define vktPrint(f, ...)                                           \
        do {                                                           \
            std::fprintf(VKT_PRINTER, "[VKT] " f "\n", ##__VA_ARGS__); \
            std::fflush(VKT_PRINTER);                                  \
        } while (0)

#else

    // Implement printer with fmt
    #include <fmt/format.h>
    #include <iostream>

    #define vktFmt(f, ...) fmt::format(f, ##__VA_ARGS__)
    #define vktOut(f)      std::cout << f << std::flush

    #define vktPrint(f, ...)                                \
        do {                                                \
            vktOut(vktFmt("[VKT] " f "\n", ##__VA_ARGS__)); \
        } while (0)

    #define vktLog(l, f, ...)                                      \
        do {                                                       \
            vktOut(vktFmt("[VKT][" l "] " f "\n", ##__VA_ARGS__)); \
        } while (0)

    #define LogW(f, ...) vktLog("W", f, ##__VA_ARGS__)
    #define LogE(f, ...) vktLog("E", f, ##__VA_ARGS__)

#endif
