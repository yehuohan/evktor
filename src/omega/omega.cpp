#include <iostream>
#include "demos.h"


int main(int argc, char *argv[]) {
    if (argc >= 2) {
        Assets::setDirs(argv[1], "./glsl");
    }
    if (argc >= 3) {
        Assets::setDirs(argv[1], argv[2]);
    }

    try {
        LnGL* p = new
            //DemoFrustum();
            //DemoFilter();
            DemoDeferred();
        p->run();
        delete p;
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
