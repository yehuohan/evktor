#version 450 core

// Fragment input
layout(location = 0) in vec3 inFragPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inTexcoord;
layout(location = 4) in vec3 inCubecoord;

// Fragment output
layout(location = 0) out vec4 outColor;

// Fragment uniform
uniform int meshType;
uniform vec3 meshColor;
uniform sampler2D meshTexture;
uniform samplerCube meshCubemap;


void main() {
    if      (-1 == meshType) { outColor = vec4(inNormal, 1.0); }
    else if ( 0 == meshType) { outColor = vec4(inColor, 1.0); }
    else if ( 1 == meshType) { outColor = vec4(meshColor, 1.0); }
    else if ( 2 == meshType) { outColor = texture(meshTexture, inTexcoord); }
    else if ( 3 == meshType) { outColor = texture(meshCubemap, inCubecoord); }
}
