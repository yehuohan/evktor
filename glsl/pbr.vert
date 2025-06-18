#version 450

layout(location = 0) in vec3 inp_position; // POSITION
layout(location = 1) in vec2 inp_texcoord; // TEXCOORD_0
layout(location = 2) in vec3 inp_normal; // NORMAL
// layout(location = 3) in vec4 inp_tangent;

layout(location = 0) out vec3 out_position;
layout(location = 1) out vec2 out_texcoord;
layout(location = 2) out vec3 out_normal;
// layout(location = 3) out vec4 out_tangent;

layout(set = 0, binding = 0) uniform GlobalUBO {
    mat4 model;
    mat4 view_proj;
} global_ubo;

void main() {
    vec4 model_position = global_ubo.model * vec4(inp_position, 1.0);
    out_position = vec3(model_position);
    out_texcoord = inp_texcoord;
    out_normal = mat3(global_ubo.model) * inp_normal;
    // out_tangent = inp_tangent;

    gl_Position = global_ubo.view_proj * model_position;
}
