#version 450 core

// Fragment input
layout(location = 0) in vec3 inFragPos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexcoord;

// Fragment multi-output
layout (location = 0) out vec3 outGBufA; // Position
layout (location = 1) out vec3 outGBufB; // Normal
layout (location = 2) out vec4 outGBufC; // Diffuse + Specular

// Material of model mesh
uniform sampler2D material_diffuse_0;
uniform sampler2D material_specular_0;


void main() {
    outGBufA = inFragPos;
    outGBufB = normalize(inNormal);
    outGBufC.rgb = texture(material_diffuse_0, inTexcoord).rgb;
    outGBufC.a = texture(material_specular_0, inTexcoord).r;
}
