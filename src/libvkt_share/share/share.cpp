#include "share.hpp"
#include <fmt/chrono.h>
#include <fstream>
#include <iostream>

NAMESPACE_BEGIN(vkt)

#define VKT_SHARE_PRINT2FILE

static std::fstream fout;

void print(const std::string& str) {
#ifdef VKT_SHARE_PRINT2FILE
    if (!fout.is_open()) {
        fout.open("log.txt", std::ios::out);
    }
    fout << fmt::format("[{:%F %T}]", fmt::localtime(std::time(nullptr))) << str;
#endif
    std::cout << str << std::flush;
}

NAMESPACE_END(vkt)
