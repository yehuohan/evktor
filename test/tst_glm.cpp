#include <glm/glm.hpp>
#include <glm/gtx/io.hpp>
#include <iostream>

void compute_mvp() {
    std::cout << "===============================================================================\n";
    glm::mat4 mmodel = glm::mat4(1.0);
    // mmodel = glm::translate(mmodel, glm::vec3(1.0f, 1.0f, 1.0f));
    // mmodel = glm::scale(mmodel, glm::vec3(5.0f, 5.0f, 5.0f));
    // mmodel = glm::rotate(mmodel, (float)glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 mview = glm::lookAt(glm::vec3(0.0, 0.0, 5.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

    // (znear, zfar): 距离eye的距离，不是坐标
    glm::mat4 mproj = glm::perspective(glm::radians(45.0), 1.0 / 1.0, 0.1, 100.0);
    // glm::mat4 mproj = glm::ortho(-160.0f, 160.0f, -160.0f, 160.0f, -1.0f, 10.0f);

    glm::mat4 mvp = mproj * mview * mmodel;
    std::cout << "mvp: " << mvp << std::endl;

    glm::vec4 pos = mvp * glm::vec4(0.2, 0.2, 0.5, 1.0);
    std::cout << "pos: " << pos << std::endl;

    pos = mvp * glm::vec4(0.2, 0.2, -0.5, 1.0);
    std::cout << "pos: " << pos << std::endl;
}

void compute_jitter() {
    std::cout << "===============================================================================\n";
    glm::mat4 mview = glm::lookAt(glm::vec3(0.0, 0.0, 5.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 mproj = glm::perspective(glm::radians(45.0), 1.0 / 1.0, 0.1, 100.0);
    glm::vec4 pos = glm::vec4(0.5, 0.5, 1.0, 1.0);

    glm::vec4 pa;
    {
        glm::mat4 vp = mproj * mview;
        std::cout << "vp (without jitter): " << vp << std::endl;
        pa = vp * pos;
        pa /= pa.w;
        std::cout << "pa (without jitter):\n" << pa << std::endl;
    }

    // Apply jitter
    glm::vec2 jitter(0.1, -0.1);
    {
        std::cout << "jitter: " << jitter << std::endl;
        mproj[2][0] += jitter.x;
        mproj[2][1] += jitter.y;
    }

    glm::vec4 pb;
    {
        glm::mat4 vp = mproj * mview;
        std::cout << "vp (with jitter): " << vp << std::endl;
        pb = vp * pos;
        pb /= pb.w;
        std::cout << "pb (with jitter):\n" << pb << std::endl;
    }

    auto pc = glm::vec2(pb) + jitter;
    auto res = (pc == glm::vec2(pa)) ? "true" : "false";
    std::cout << "pb + jitter == pa : " << res << std::endl;
}

int main() {
    compute_mvp();
    compute_jitter();
}
