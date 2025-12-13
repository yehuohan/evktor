#include "shader.hpp"
#include "shader_glsl.hpp"
#include <fstream>

NAMESPACE_BEGIN(vkt)

using namespace core;

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
    auto res = ShaderGlsl::get().compile(shader.stage, shader.filename, source.code, shader.entry);
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
