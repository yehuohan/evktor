#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/io.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>

/**
 * @brief Compute model-view-projection
 *
 * - 数学上，P * M 称作 P左乘M；
 *   GLSL/GLM中，需要写成 M * P 的形式，表示按矩阵M对P进行变换。
 *
 * - GLSL/GLM中的矩阵使用column-major，内存按列存储，使用M[col][row]的索引方式；
 *   使用GLSL/GLM中的矩阵时，不要在‘矩阵数学形式’和‘内存排列顺序’之间做联想，
 *   而直接从‘矩阵数学形式’和索引‘M[col][row]’考虑矩阵计算，例如：
 *      变换矩阵 M = [[R, T],                       => 矩阵数学形式
 *                    [0, 1]]
 *      平移向量 T = { M[3][0], M[3][1], M[3][3] }  => 索引M[col][row]
 */
void compute_mvp() {
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
    glm::vec2 msize = glm::vec2(1920.0f, 1080.0f);
    glm::mat4 mview = glm::lookAt(glm::vec3(0.0, 0.0, 5.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 mproj = glm::perspective(glm::radians(45.0), 1.0 / 1.0, 0.1, 100.0);
    glm::vec4 mpos = glm::vec4(0.5, 0.5, 1.0, 1.0);

    std::cout << glm::io::width(10) << glm::io::precision(6);

    glm::vec4 ndc;
    glm::vec2 pos;
    {
        glm::mat4 vp = mproj * mview;
        std::cout << "vp: " << vp << std::endl;
        ndc = vp * mpos;
        ndc /= ndc.w;
        pos = ((glm::vec2(ndc) + 1.0f) / 2.0f) * msize;
        std::cout << "pos: " << pos << std::endl;
    }

    // Apply jitter
    bool unreal_or_unity = true;
    glm::vec2 jitter(0.125, -0.375);
    glm::vec2 jitter_ndc = jitter / msize * 2.0f;
    {
        std::cout << "jitter: " << jitter << std::endl;
        if (unreal_or_unity) {
            mproj[2][0] += jitter_ndc.x;
            mproj[2][1] += jitter_ndc.y;
        } else {
            mproj = glm::translate(glm::mat4(1.0), glm::vec3(jitter_ndc, 0.0)) * mproj;
            // Equal to
            // mproj[2][0] -= jitter_ndc.x;
            // mproj[2][1] -= jitter_ndc.y;
        }
    }

    {
        glm::mat4 vp = mproj * mview;
        std::cout << "vp: " << vp << std::endl;
        ndc = vp * mpos;
        ndc /= ndc.w;
        pos = ((glm::vec2(ndc) + 1.0f) / 2.0f) * msize;
        std::cout << "pos: " << pos << std::endl;
        // 按6位小数打印时不完全相等，貌似精度不够
        if (unreal_or_unity) {
            std::cout << "pos+jitter: " << pos + jitter << std::endl;
        } else {
            std::cout << "pos-jitter: " << pos - jitter << std::endl;
        }
    }
}

void compute_quat() {
    float ang = glm::radians(90.0f);
    glm::vec3 axis = glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat rot;
    rot = glm::quat(glm::cos(ang / 2.0),
                    axis.x * glm::sin(ang / 2.0),
                    axis.y * glm::sin(ang / 2.0),
                    axis.z * glm::sin(ang / 2.0));
    std::cout << "rot: " << rot << std::endl;

    rot = glm::angleAxis(ang, axis);
    std::cout << "rot: " << rot << std::endl;
    std::cout << "rot.mat4: " << glm::toMat4(rot) << std::endl;

    // Rotation only works on `xyz`
    glm::vec4 pos = rot * glm::vec4(1.0, 0.0, 0.0, 10.0);
    std::cout << "rot * pos: " << pos << std::endl;
}

void case_dep_glm() {
    // compute_mvp();
    compute_jitter();
    // compute_quat();
}
