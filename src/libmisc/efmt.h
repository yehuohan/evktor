#pragma once
#include <string>
#include <stdexcept>
#include <fmt/core.h>


#if 1
#define _eformat(f, ...)      std::runtime_error(fmt::format(f, ##__VA_ARGS__))
#define eformat(f, ...)       _eformat(__FILE__ ":{}:0: error: " f, __LINE__, ##__VA_ARGS__)
#else
#define _eformat(fmt, ...)      std::runtime_error(string_format(fmt, ##__VA_ARGS__))
#define eformat(fmt, ...)       _eformat(__FILE__ ":%d:0: error: " fmt, __LINE__, ##__VA_ARGS__)

std::string string_format(const char* fmt, ...);
#endif
