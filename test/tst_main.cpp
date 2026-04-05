#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <tiny_gltf.h>

#include "__helpers.hpp"
#include <cxxopts.hpp>
#include <iostream>
#include <map>

#include "tst_generated.hpp"

int main(int argc, char* argv[]) {
    cxxopts::Options opts{"evktor"};
    auto adder = opts.add_options();
    adder("c,case", "Setup testcase", cxxopts::value<std::string>()->default_value(""));
    adder("a,assets", "Setup asset path", cxxopts::value<std::string>()->default_value("./assets"));
    adder("s,shaders", "Setup shader path", cxxopts::value<std::string>()->default_value("./shaders"));
    opts.parse_positional("case");

    auto res = opts.parse(argc, argv);
    vktdev::Assets::setDirs(res["assets"].as<std::string>(), res["shaders"].as<std::string>());

    auto case_name = res["case"].as<std::string>();
    if (case_name == "") {
        for (const auto& item : cases) {
            std::cout << "[tst]>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
            std::cout << "[tst] " << item.first << std::endl;
            item.second();
        }
    } else {
        if (auto it = cases.find(String("case_") + case_name); it != cases.end()) {
            std::cout << "[tst]>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
            it->second();
            std::cout << "[tst]<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
        } else {
            std::cout << "Not supported case: " << case_name << std::endl;
        }
    }
}
