#pragma once
#include <fstream>
#include <share/helpers.hpp>
#include <share/share.hpp>
#include <string>

#define tstOut(f, ...) vkt::print(vktFmt("[tst] " f "\n", ##__VA_ARGS__))

typedef void (*FnCaseVoid)(void);
