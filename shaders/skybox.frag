#version 460

layout(location = 0) in vec3 inp_texcoord;
layout(location = 0) out vec4 out_color;

layout(binding = 1) uniform samplerCube skybox;

void main() {
    out_color = texture(skybox, inp_texcoord);
}
