/*!
 * @file font.h
 * @brief font renderer
 *
 */

#ifndef FONT_RENDERER_H
#define FONT_RENDERER_H

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <map>
#include <cstdint>

#include "shader.h"


/*!
 * @brief Character attributes
 *
 */
struct Character {
    uint32_t        id;
    glm::ivec2      size;
    glm::ivec2      bearing;
    uint32_t        advance;
};


/*!
 * @brief Text renderer with font
 *
 */
class TextRenderer {
public:
    std::map<char, Character> characters; 
    Shader txt_shader;

    /*!
     * @brief 创建本文渲染
     *
     * w,h为窗口大小
     */
    TextRenderer(uint32_t w, uint32_t h);

    void load(const std::string& font, uint32_t fontsize);

    void renderText(const std::string& text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));

private:
    uint32_t vao, vbo;
};

#endif /* end of include guard: FONT_RENDERER_H */
