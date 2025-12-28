#version 450 core

out vec4 fragColor;
in vec2 texCoord;

uniform sampler2D text;
uniform vec3 textColor;


void main() {
    vec4 spl = vec4(1.0, 1.0, 1.0, texture(text, texCoord).r); // 使用纹理的红色分量
    fragColor = vec4(textColor, 1.0) * spl; // 纹理颜色处（字形像素处）不透明，即显示出字体了
}
