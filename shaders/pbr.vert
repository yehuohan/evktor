#version 460

layout(location = 0) in vec3 position; // GLTF: POSITION
layout(location = 1) in vec2 texcoord_0; // GLTF: TEXCOORD_0
layout(location = 2) in vec3 normal; // GLTF: NORMAL

layout(location = 0) out vec3 out_position;
layout(location = 1) out vec2 out_texcoord;
layout(location = 2) out vec3 out_normal;

layout(set = 0, binding = 0) uniform PBRUniform {
    mat4 model;
    mat4 view_proj;
} pbr_ubo;

void main() {
    vec4 model = pbr_ubo.model * vec4(position, 1.0);
    out_position = vec3(model);
    out_texcoord = texcoord_0;
    out_normal = mat3(pbr_ubo.model) * normal;

    gl_Position = pbr_ubo.view_proj * model;
}
