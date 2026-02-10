#version 460

layout(location = 0) in vec3 inp_position;
layout(location = 1) in vec2 inp_texcoord;
layout(location = 2) in vec3 inp_normal;

layout(location = 0) out vec4 out_color;

layout(set = 0, binding = 0) uniform PBRUniform {
    mat4 model;
    mat4 view_proj;
} pbr_ubo;

layout(set = 0, binding = 1) uniform sampler2D base_color_texture;
#ifdef HAS_BASE_COLOR_TEXTURE
#endif

#ifdef HAS_NORMAL_TEXTURE
layout(set = 0, binding = 2) uniform sampler2D normal_texture;
#endif

#ifdef HAS_METALLIC_ROUGHNESS_TEXTURE
layout(set = 0, binding = 3) uniform sampler2D metallic_roughness_texture;
#endif

void main() {
    vec4 base_color = vec4(0.0, 0.0, 0.0, 1.0);
    base_color = texture(base_color_texture, inp_texcoord);

    // #ifdef HAS_BASE_COLOR_TEXTURE
    // base_color = texture(base_color_texture, in_uv);
    // #else
    // base_color = pbr_material_uniform.base_color_factor;
    // #endif

    out_color = base_color;
}
