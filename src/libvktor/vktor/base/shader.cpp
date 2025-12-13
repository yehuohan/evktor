#include "shader.hpp"
#include "shader_glsl.hpp"
#include <algorithm>
#include <fstream>

NAMESPACE_BEGIN(vkt)

using namespace core;

ShaderState::Self ShaderState::setDefine(const String& name, const String& value) {
    auto iter = std::find_if(defines.begin(), defines.end(), [&name](const std::pair<String, String> item) {
        return name == item.first;
    });
    if (iter != defines.end()) {
        iter->first = name;
        iter->second = value;
    } else {
        defines.push_back(std::make_pair(name, value));
    }
    return *this;
}

ShaderState::Self ShaderState::delDefine(const String& name) {
    auto iter = std::find_if(defines.begin(), defines.end(), [&name](const std::pair<String, String> item) {
        return name == item.first;
    });
    if (iter != defines.end()) {
        defines.erase(iter);
    }
    return *this;
}

ShaderState::Self ShaderState::delAllDefines() {
    defines.clear();
    return *this;
}

String ShaderState::getPreamble() const {
    String preamble("");
    for (const auto& item : defines) {
        preamble += vktFmt("#define {} {}\n", item.first, item.second);
    }
    return std::move(preamble);
}

ShaderSource::ShaderSource(const String& _filename, String&& _code) {
    filename = _filename;
    code = std::move(_code);
    id = hash(code);
}

ShaderSource::ShaderSource(ShaderSource&& rhs) {
    filename = std::move(rhs.filename);
    code = std::move(rhs.code);
    id = rhs.id;
    rhs.id = 0;
}

Res<Shader> Shader::from(const ShaderSource& source, const ShaderState& state) {
    Shader shader{state.stage, source.filename, state.entry};

    auto res = ShaderGlsl::get().compile(shader.stage, shader.filename, source.code, shader.entry, state.getPreamble());
    OnErr(res);
    shader.spv_code = res.unwrap();
    shader.id = hash(String{reinterpret_cast<const char*>(shader.spv_code.data()),
                            reinterpret_cast<const char*>(shader.spv_code.data() + shader.spv_code.size())});

    return Ok(std::move(shader));
}

Shader::Shader(Shader&& rhs) : stage(rhs.stage), filename(rhs.filename), entry(rhs.entry) {
    spv_code = std::move(rhs.spv_code);
    id = rhs.id;
    rhs.id = 0;
    desc_sets = std::move(rhs.desc_sets);
}

Res<ShaderModule> Shader::into(const CoreApi& api) const {
    return ShaderModuleState(vktFmt("ShaderModule({})", filename)).setCode(spv_code).into(api);
}

NAMESPACE_END(vkt)
