#include "__helpers.hpp"
#include <fmt/core.h>

const Quad quad{};

Quad::Quad() {
    wid = 9;
    hei = 9;
    cha = 4;
    num = wid * hei * cha;

    comp_file = vktdev::Assets::shader("test/quad.comp");
    group_count_x = (wid + 7) / 8;
    group_count_y = (hei + 7) / 8;
    group_count_z = 1;
    img.resize(num);
    for (int k = 0; k < num; k++) {
        img[k] = k + 1;
    }
}

void Quad::checkOutput(const Vector<float>& out) const {
    for (size_t k = 0; k < num; k++) {
        uint32_t rhs = (k + 1) * 10;
        if ((k + 1) % 4 == 0) {
            rhs = 1;
        }
        assert((uint32_t)out[k] == rhs);
    }
    const Vector<float> rhs{out.data(), out.data() + 12};
    tstOut("Output: {}", vec2str(rhs));
}

float Triangle::vertices[24] = {
    // pos,             color,            uv
    -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 左下角
    1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // 右下角
    0.0f,  1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, // 上中
};

uint32_t Triangle::indices[3] = {0, 1, 2};

const char* Triangle::out_color[9] = {
    "#########",
    "####*####",
    "####*####",
    "###***###",
    "###***###",
    "##*****##",
    "##*****##",
    "#*******#",
    "#########",
};

Triangle::Triangle() {
    wid = 9;
    hei = 9;
    cha = 4;
    num = wid * hei * cha;

    vert_file = vktdev::Assets::shader("test/triangle.vert");
    frag_file = vktdev::Assets::shader("test/triangle.frag");
    ubo.view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f) /* eye */,
                           glm::vec3(0.0f, 0.0f, 0.0f) /* center */,
                           glm::vec3(0.0f, 1.0f, 0.0f) /* up */);
    ubo.proj = glm::perspective(glm::radians(45.0f), (float)wid / hei, 0.1f, 100.0f);
    tex = Vector<float>(num, 1.0);
}

void Triangle::checkOutput(const Vector<float>& out) const {
    tstOut("Output:");
    for (size_t r = 0; r < hei; r++) {
        String line("\0", wid + 1);
        for (size_t c = 0; c < wid; c++) {
            size_t idx = (r * wid + c) * cha;
            float gray = (out[idx + 0] + out[idx + 1] + out[idx + 2]) / 3.0;
            line[c] = gray > 0.5 ? '*' : '#';
            assert(line[c] == out_color[r][c]);
        }
        line[wid] = '\0';
        tstOut("{}", line);
    }
}

Box<CoreApi> createCoreApi(const Vector<const char*> inst_exts, const Vector<const char*> dev_exts) {
    Vktor vkt{};
    vkt.createApi(inst_exts, dev_exts);
    auto api = std::move(vkt.api);

    tstOut("Instance: {}, Physical Device: {}, Device: {}",
           fmt::ptr((VkInstance)*api),
           fmt::ptr((VkPhysicalDevice)*api),
           fmt::ptr((VkDevice)*api));

    return std::move(api);
}
