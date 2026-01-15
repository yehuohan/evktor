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
    push_args.scaler = 9;
    spec_args.alpha = 2.0;
    img.resize(num);
    for (uint32_t k = 0; k < num; k++) {
        img[k] = k + 1;
    }
}

void Quad::checkOutput(const Vector<float>& out) const {
    for (size_t k = 0; k < num; k++) {
        uint32_t rhs = (k + 1) * push_args.scaler;
        if ((k + 1) % 4 == 0) {
            rhs = spec_args.alpha;
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
    push_args.flipy = 1;
    push_args.scaler = 2;
    spec_args.alpha = 3;
    ubo.view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f) /* eye */,
                           glm::vec3(0.0f, 0.0f, 0.0f) /* center */,
                           glm::vec3(0.0f, 1.0f, 0.0f) /* up */);
    ubo.proj = glm::perspective(glm::radians(45.0f), (float)wid / hei, 0.1f, 100.0f);
    tex = Vector<float>(num, 1.0);
}

void Triangle::checkOutput(const Vector<float>& out) const {
    tstOut("Output:");
    for (size_t r = 0; r < hei; r++) {
        String line("\0", wid);
        for (size_t c = 0; c < wid; c++) {
            size_t idx = (r * wid + c) * cha;
            glm::vec4 pix = glm::vec4(out[idx + 0], out[idx + 1], out[idx + 2], out[idx + 3]);
            float gray = (pix.r + pix.b + pix.b) / 3.0;
            if (gray > 0.0) {
                line[c] = '*';
                assert((uint32_t)pix.a == (uint32_t)(spec_args.alpha * push_args.scaler));
            } else {
                line[c] = '#';
                assert((uint32_t)pix.a == 0);
            }
        }
        tstOut("{}", line);
        assert(line == String(out_color[push_args.flipy ? hei - r - 1 : r]));
    }
}

Box<CoreApi> createCoreApi(const Vector<const char*> inst_exts, const Vector<const char*> dev_exts) {
    Vktor vkt{};
    vkt.createApi(
        [&inst_exts](InstanceState& iso) {
            iso.addExtensions(inst_exts);
        },
        nullptr,
        nullptr,
        [&dev_exts]([[maybe_unused]] const PhysicalDevice& phydev, DeviceState& dso) {
            dso.addExtensions(dev_exts);
        });
    auto api = std::move(vkt.api);

    tstOut("Instance: {}, Physical Device: {}, Device: {}",
           fmt::ptr((VkInstance)*api),
           fmt::ptr((VkPhysicalDevice)*api),
           fmt::ptr((VkDevice)*api));

    return api;
}
