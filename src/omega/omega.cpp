#include <iostream>
#include "assets.h"
#include "demos.h"


int main(int argc, char *argv[]) {
    if (argc >= 2) {
        Assets::setDir(argv[1]);
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
