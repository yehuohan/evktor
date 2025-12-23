#include "__helpers.hpp"
#include <iostream>
#include <map>

#include "tst_generated.hpp"

int main(int argc, char* argv[]) {
    vktdev::Assets::setDirs("../assets", "./glsl");

    std::cout << "[tst]>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    if (argc >= 2) {
        auto res = cases.find(String("case_") + argv[1]);
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
