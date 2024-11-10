#include "__helpers.hpp"
#include <iostream>
#include <map>

extern void case_core();
extern void case_glm();
extern void case_glslang();
extern void case_result();

static const std::map<std::string, FnCaseVoid> cases{
    {   "case_core",    case_core},
    {    "case_glm",     case_glm},
    {"case_glslang", case_glslang},
    { "case_result",  case_result},
};

int main(int argc, char* argv[]) {
    std::cout << "[tst]>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    if (argc >= 2) {
        auto res = cases.find(std::string("case_") + argv[1]);
        if (res != cases.end()) {
            res->second();
        } else {
            std::cout << "Not supported case: " << argv[1] << std::endl;
        }
    } else {
        for (const auto& item : cases) {
            item.second();
        }
    }
    std::cout << "[tst]<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
}
