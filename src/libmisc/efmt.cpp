#include "efmt.h"
#include <cstdarg>
#include <cstring>

std::string string_format(const char* fmt, ...) {
    char buf[1024]; // 1024 bytes at max length
    memset(buf, 0, 1024);
    va_list va;
    va_start(va, fmt);
    vsnprintf(buf, 1023, fmt, va);
    va_end(va);

    std::string err(buf, strlen(buf));
    return err;
}
