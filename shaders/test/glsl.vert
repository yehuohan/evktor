#version 460

layout(location = 0) in vec3 inp_pos;

layout(location = 0) out vec3 out_pos;

#ifdef TST_ERROR
    asd
#endif

void main() {
    gl_Position =  vec4(inp_pos, 1.0);
    out_pos = inp_pos;
}

