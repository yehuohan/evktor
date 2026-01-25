#version 460

layout(location = 0) in vec3 inp_color;
layout(location = 1) in vec2 inp_uv;

layout(location = 0) out vec4 out_color;

layout(set = 0, binding = 1) uniform sampler2D tex;

layout(push_constant) uniform Args {
    layout(offset = 20) int scaler; // Specify offset to 20 bytes
} args;

layout(constant_id = 0) const int alpha = 1;

void main() {
    vec3 color = inp_color + texture(tex, inp_uv).rgb;
    out_color = vec4(color, float(alpha * args.scaler));
}
