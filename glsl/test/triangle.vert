#version 450

layout(location = 0) out vec3 out_color;

vec2 triangle_positions[3] = vec2[](
    vec2(0.5, -0.5),
    vec2(0.5, 0.5),
    vec2(-0.5, 0.5)
);

vec3 triangle_colors[3] = vec3[](
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 1.0)
);

#ifdef TST_ERROR
    asdf
#endif

void main() {
    gl_Position = vec4(triangle_positions[gl_VertexIndex], 0.0, 1.0);
    out_color = triangle_colors[gl_VertexIndex];
}
