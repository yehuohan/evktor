#version 460

layout(location = 0) in vec3 inp_color;
layout(location = 1) in vec3 inp_normal;
layout(location = 2) in vec2 inp_texcoord;

layout(location = 0) out vec4 out_color;

layout(set = 0, binding = 1) uniform sampler2D tex;

#ifdef HAS_TEX
layout(constant_id = 0) const int use_color = 0;
#endif

void main() {
    #ifdef HAS_TEX
    out_color = texture(tex, inp_texcoord);
    #else
    out_color = vec4(inp_color, 1.0);
    #endif
}
