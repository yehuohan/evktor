#version 450

layout(location = 0) in vec3 inp_color;
layout(location = 1) in vec2 inp_uv;

layout(location = 0) out vec4 out_color;

layout(set = 0, binding = 1) uniform sampler2D tex;

void main() {
    vec3 color = mix(texture(tex, inp_uv).rgb, inp_color, 0.5);
    out_color = vec4(color, 1.0);
}
