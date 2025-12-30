#include "shader.hpp"
#include "shader_glsl.hpp"
#include <algorithm>
#include <fstream>

NAMESPACE_BEGIN(vkt)

using namespace core;

using Self = Shader::Self;

Shader::Shader(Shader&& rhs) {
    src = std::move(rhs.src);
    src_path = std::move(rhs.src_path);
    src_id = rhs.src_id;
    src_defs = std::move(rhs.src_defs);
    rhs.src_id = 0;

    stage = rhs.stage;
    entry = rhs.entry;
    spv = std::move(rhs.spv);
    spv_id = rhs.spv_id;
    rhs.spv_id = 0;

    desc_sets = std::move(rhs.desc_sets);
}

Shader Shader::from(const VkShaderStageFlagBits stage, String&& source, const String& fullpath) {
    Shader shader{};
    shader.stage = stage;
    shader.src = std::move(source);
    shader.src_id = hash(shader.src);
    shader.src_path = fullpath;
    return std::move(shader);
}

Res<ShaderModule> Shader::into(const CoreApi& api) const {
    auto cur_id = hash(*this);
    if (spv_id != hash(*this)) {
        auto res = ShaderGlsl::get().compile(stage, src, entry, getPreamble(), src_path);
        OnErr(res);
        spv = res.unwrap();
        spv_id = cur_id;
    }
    return ShaderModuleState(vktFmt("ShaderModule({})", src_id)).setCode(spv).into(api);
}

Shader::Self Shader::setDefine(const String& name, const String& value) {
    auto iter = std::find_if(src_defs.begin(), src_defs.end(), [&name](const std::pair<String, String> item) {
        return name == item.first;
    });
    if (iter != src_defs.end()) {
        iter->first = name;
        iter->second = value;
    } else {
        src_defs.push_back(std::make_pair(name, value));
    }
    return *this;
}

Shader::Self Shader::delDefine(const String& name) {
    auto iter = std::find_if(src_defs.begin(), src_defs.end(), [&name](const std::pair<String, String> item) {
        return name == item.first;
    });
    if (iter != src_defs.end()) {
        src_defs.erase(iter);
    }
    return *this;
}

Shader::Self Shader::delAllDefines() {
    src_defs.clear();
    return *this;
}

String Shader::getPreamble() const {
    String preamble("");
    for (const auto& item : src_defs) {
        preamble += vktFmt("#define {} {}\n", item.first, item.second);
    }
    return std::move(preamble);
}

Self Shader::setEntry(const String& _entry) {
    entry = _entry;
    return *this;
}

NAMESPACE_END(vkt)
