#pragma once
#include <fstream>
#include <share/share.hpp>
#include <string>

#define tstOut(f, ...) vkt::print(vktFmt("[tst] " f "\n", ##__VA_ARGS__))

typedef void (*FnCaseVoid)(void);

static std::string read_shader(const std::string& filename) {
    std::ifstream fin(filename, std::ios::in);
    if (!fin.is_open()) {
        throw std::runtime_error("Failed to read shader " + filename);
    }
    return std::string({std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>()});
}
