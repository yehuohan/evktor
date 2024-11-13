#version 450

layout(location = 0) in vec3 inp_pos;
layout(location = 1) in vec3 inp_color;
layout(location = 2) in vec2 inp_uv;

layout(location = 0) out vec3 out_color;
layout(location = 1) out vec2 out_uv;

layout(set = 0, binding = 0) uniform UBO {
    mat4 view;
    mat4 proj;
} ubo;

#ifdef TST_ERROR
    asd
#endif

void main() {
    gl_Position = ubo.proj * ubo.view * vec4(inp_pos, 1.0);
    out_color = inp_color;
    out_uv = inp_uv;
}
