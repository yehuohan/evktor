#version 460

layout(location = 0) in vec3 inp_pos;
layout(location = 1) in vec3 inp_color;
layout(location = 2) in vec2 inp_uv;

layout(location = 0) out vec3 out_color;
layout(location = 1) out vec2 out_uv;

layout(set = 0, binding = 0) uniform UBO {
    mat4 view;
    mat4 proj;
} ubo;

layout(push_constant) uniform Args {
    int flipy;
} args;

void main() {
    vec4 pos = vec4(inp_pos, 1.0);
    if (bool(args.flipy)) {
        pos.y = -pos.y;
    }
    gl_Position = ubo.proj * ubo.view * pos;
    out_color = inp_color;
    out_uv = inp_uv;
}
