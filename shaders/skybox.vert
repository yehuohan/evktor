#version 460

layout(location = 0) in vec3 position;

layout(binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 proj;
} ubo;

layout(location = 0) out vec3 out_texcoord;

void main() {
    out_texcoord = position; // 直接使用位置坐标作为纹理坐标
    gl_Position = ubo.proj * mat4(mat3(ubo.view)) * vec4(position, 1.0).xyww;
}
