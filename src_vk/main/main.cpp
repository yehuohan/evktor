#include <exception>
#include <iostream>

int main(int argc, char* argv[]) {
    try {
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
