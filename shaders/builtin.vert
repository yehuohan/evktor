#version 460

layout(location = 0) in vec3 inp_pos;
layout(location = 1) in vec3 inp_color;
layout(location = 2) in vec3 inp_normal;
layout(location = 3) in vec2 inp_texcoord;

layout(location = 0) out vec3 out_pos;
layout(location = 1) out vec3 out_color;
layout(location = 2) out vec3 out_normal;
layout(location = 3) out vec2 out_texcoord;

layout(set = 0, binding = 0) uniform BuiltinUniform {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

void main() {
    out_pos = inp_pos;
    out_color = inp_color;
    out_normal = inp_normal;
    out_texcoord = inp_texcoord;
    #ifdef HAS_SKYBOX
    vec4 clip_pos = ubo.proj * mat4(mat3(ubo.view)) * vec4(inp_pos, 1.0); // mat3(ubo.view): remove translation
    gl_Position = vec4(clip_pos.xy, 0.0, clip_pos.w); // Reversed-z: far is 0.0
    #else
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inp_pos, 1.0);
    #endif
}
