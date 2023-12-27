#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 inp_color;
layout(location = 1) in vec3 inp_normal;
layout(location = 2) in vec2 inp_texcoord;

layout(location = 0) out vec4 out_color;

layout(set = 0, binding = 1) uniform sampler2D mesh_tex;
// layout(set = 0, binding = 2) uniform samplerCube mesh_cube;

void main() {
    // out_color = vec4(inp_color, 1.0);
    out_color = texture(mesh_tex, inp_texcoord);
}
