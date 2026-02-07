#include "printer.hpp"

void fmtWrite(const String& str) {
    static std::fstream fout;
    if (!fout.is_open()) {
        fout.open("log.txt", std::ios::out);
    }
    fout << str << std::endl;
}
