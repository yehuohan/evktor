
#include "font.h"
#include "shader.h"

#include <ft2build.h>
#include FT_FREETYPE_H


TextRenderer::TextRenderer(uint32_t w, uint32_t h) {
    txt_shader.load("glsl/omega/font/text2d.vert", "glsl/omega/font/text2d.frag");
    txt_shader.use().setMat4("projection", glm::ortho(0.0f, static_cast<float>(w), static_cast<float>(h), 0.0f));

    // 设置顶点数据
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // 每个2D文本需要6个顶点，每个顶点需要4个float(顶点坐标+纹理坐标)
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderer::load(const std::string &font, uint32_t fontsize) {
    characters.clear();

    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR:FREETYPE: Could not init freetype library" << std::endl;
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, font.c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, fontsize); // 0表示通过给定高度动态计算宽度
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // 通常纹理要求4字节对齐，这里使用一个字节表示纹理颜色，按1字节对齐

    // 加载ascii字符
    for (unsigned char c = 0; c < 128; c ++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
        } else {
            uint32_t tid;
            glGenTextures(1, &tid);
            glBindTexture(GL_TEXTURE_2D, tid);
            glTexImage2D(GL_TEXTURE_2D, 
                    0,
                    GL_RED, // bitmap是一个8位灰度图，纹理颜色用一个字节表示
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            Character ch = {
                tid,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                (uint32_t)face->glyph->advance.x
            };
            characters.insert(std::pair<char, Character>(c, ch));
        }
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextRenderer::renderText(const std::string& text, float x, float y, float scale, glm::vec3 color) {
    txt_shader
        .use()
        .setVec3("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);

    for (auto c : text) {
        Character ch = characters[c];

        float xpos = x + ch.bearing.x * scale;
        //float ypos = y - (ch.size.y - ch.bearing.y) * scale;
        float ypos = y + (characters['H'].bearing.y - ch.bearing.y) * scale;
        float w = ch.size.x * scale;
        float h = ch.size.y * scale;

        float vertics[6][4] = {
            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f },
            { xpos,     ypos,       0.0f, 0.0f },

            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f }
        };
        glBindTexture(GL_TEXTURE_2D, ch.id);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertics), vertics);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.advance >> 6) * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
