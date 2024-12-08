#include "app.h"
#include <exception>
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        App app(argc, argv);
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
