#version 450 core

// Vertex input
layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexcoord;

// Vertex output
layout(location = 0) out vec3 outFragPos;
layout(location = 1) out vec3 outNormal;
layout(location = 2) out vec2 outTexcoord;

// Vertex uniform
uniform mat4 model; // 模型变换
uniform mat4 view; // 视图变换
uniform mat4 proj; // 投影变换


void main() {
    vec4 worldPos = model * vec4(inPos, 1.0);
    outFragPos = worldPos.xyz;
    // 模型变换时，其法线也会变化
    // - 等比变换不会破坏法线
    // - 不等比变换会导致法向量不再垂直表面，需要使用法线矩阵校正
    outNormal = mat3(transpose(inverse(model))) * inNormal;
    outTexcoord = inTexcoord;
    gl_Position = proj * view * worldPos;
}

