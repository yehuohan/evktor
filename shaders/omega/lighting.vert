#version 450 core

// Vertex input
layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inTexcoord;

// Vertex output
layout(location = 0) out vec2 outTexcoord;


void main() {
    outTexcoord = inTexcoord;
    gl_Position = vec4(inPos, 1.0);
}
