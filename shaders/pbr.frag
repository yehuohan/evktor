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

void main() {
    vec4 base_color = texture(base_color_texture, inp_texcoord);

    out_color = base_color;
}
