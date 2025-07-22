#pragma once
#include <fstream>
#include <share/helpers.hpp>
#include <share/share.hpp>
#include <string>

#define tstOut(f, ...) vkt::print(vktFmt("[tst] " f "\n", ##__VA_ARGS__))

typedef void (*FnCaseVoid)(void);

static String read_shader(const String& filename) {
    std::ifstream fin(filename, std::ios::in);
    if (!fin.is_open()) {
        throw std::runtime_error("Failed to read shader " + filename);
    }
    return String({std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>()});
}
