#version 450 core

// Vertex input
layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inTexcoord;

// Vertex output
layout(location = 0) out vec3 outFragPos;
layout(location = 1) out vec3 outColor;
layout(location = 2) out vec3 outNormal;
layout(location = 3) out vec2 outTexcoord;
layout(location = 4) out vec3 outCubecoord;

// Vertex uniform
uniform int meshType;
uniform mat4 model; // 模型变换
uniform mat4 view; // 视图变换
uniform mat4 proj; // 投影变换


void main() {
    vec4 worldPos = model * vec4(inPos, 1.0);
    outFragPos = worldPos.xyz;
    outColor = inColor;
    outNormal = mat3(transpose(inverse(model))) * inNormal;
    outTexcoord = inTexcoord;
    outCubecoord = inPos;

    if (3 == meshType) {
        // Sky box的z均设为设为最大深度1.0
        gl_Position = (proj * view * vec4(inPos, 1.0)).xyww;
    } else {
        gl_Position = proj * view * worldPos;
    }
}
