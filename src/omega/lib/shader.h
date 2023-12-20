
/*!
 * @file shader.h
 * @brief 着色器管理
 *
 */

#ifndef SHADER_H
#define SHADER_H

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>

class Shader {

public:
    unsigned int id;

    Shader() { }

    /*!
     * @brief 加载着色器代码
     *
     * @param vertexPath 顶点着色器代码路径
     * @param fragmentPath 片段着色器代码路径
     */
    void load(const std::string& vertexPath, const std::string& fragmentPath);

    /*!
     * @brief 编译着色器程序
     *
     * 参数为着色器代码文本。
     *
     */
    void compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource = nullptr);

    /*!
     * @brief 加载compute shader代码
     *
     */
    void load(const std::string& compPath);

    /*!
     * @brief 编译compute shader代码
     *
     */
    void compile(const char *compSource);

    Shader& use() { glUseProgram(id); return *this; }

    Shader& setBool(const std::string& name, bool value);
    Shader& setInt(const std::string& name, int value);
    Shader& setFloat(const std::string& name, float value);
    Shader& setVec2(const std::string& name, const glm::vec2& value);
    Shader& setVec2(const std::string& name, const float x, const float y);
    Shader& setVec3(const std::string& name, const glm::vec3& value);
    Shader& setVec3(const std::string& name, const float x, const float y, const float z);
    Shader& setVec4(const std::string& name, const glm::vec4& value);
    Shader& setVec4(const std::string& name, const float x, const float y, const float z, const float w);
    Shader& setMat4(const std::string& name, const glm::mat4& value);

private:
    void checkCompileErrors(unsigned int object, std::string type);
};

#endif /* end of include guard: SHADER_H */
