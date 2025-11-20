#version 450

layout(location = 0) in vec3 inp_position;
layout(location = 1) in vec2 inp_texcoord;
layout(location = 2) in vec3 inp_normal;
// layout(location = 3) in vec4 inp_tangent;

layout(location = 0) out vec4 out_color;

layout(set = 0, binding = 0) uniform GlobalUBO {
    mat4 model;
    mat4 view_proj;
} global_ubo;

layout(set = 0, binding = 1) uniform sampler2D tex_diffuse;

void main() {
    out_color = texture(tex_diffuse, inp_texcoord);
    // out_color = vec4(inp_normal, 1.0);
}
