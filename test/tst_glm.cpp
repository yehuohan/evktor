#include <glm/glm.hpp>
#include <glm/gtx/io.hpp>
#include <iostream>

int main() {
    glm::mat4 mmodel = glm::mat4(1.0);
    // mmodel = glm::translate(mmodel, glm::vec3(1.0f, 1.0f, 1.0f));
    // mmodel = glm::scale(mmodel, glm::vec3(5.0f, 5.0f, 5.0f));
    // mmodel = glm::rotate(mmodel, (float)glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 mview = glm::lookAt(glm::vec3(0.0, 0.0, 5.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

    // (znear, zfar): 距离eye的距离，不是坐标，如果平面在eys后面，需要为正值
    glm::mat4 mproj = glm::perspective(glm::radians(45.0), 1.0 / 1.0, 0.1, 100.0);
    // glm::mat4 mproj = glm::ortho(-160.0f, 160.0f, -160.0f, 160.0f, -1.0f, 10.0f);

    glm::mat4 m = mproj * mview * mmodel;
    std::cout << m << std::endl;

    glm::vec4 p = m * glm::vec4(0.2, 0.2, 0.5, 1.0);
    std::cout << p << std::endl;

    p = m * glm::vec4(0.5, 0.5, -0.5, 1.0);
    std::cout << p << std::endl;
}
