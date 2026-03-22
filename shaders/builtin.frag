#version 460

layout(location = 0) in vec3 inp_pos;
layout(location = 1) in vec3 inp_color;
layout(location = 2) in vec3 inp_normal;
layout(location = 3) in vec2 inp_texcoord;

layout(location = 0) out vec4 out_color;

#ifdef HAS_SKYBOX
layout(set = 0, binding = 1) uniform samplerCube tex;
#else

#ifdef HAS_TEX
layout(set = 0, binding = 1) uniform sampler2D tex;
#endif

#endif

void main() {
    #ifdef HAS_SKYBOX
    out_color = texture(tex, inp_pos); // Take position as cube uv directly
    #else

    #ifdef HAS_TEX
    out_color = texture(tex, inp_texcoord);
    #else
    out_color = vec4(inp_color, 1.0);
    #endif

    #endif
}
