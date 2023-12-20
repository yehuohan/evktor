
#include "shader.h"

#include <fstream>
#include <sstream>


void Shader::load(const std::string& vertexPath, const std::string& fragmentPath) {
    // 读取着色器代码
    std::string vertexCode, fragmentCode;
    std::ifstream vertexFile, fragmentFile;
    vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vertexFile.open(vertexPath);
        fragmentFile.open(fragmentPath);
        std::stringstream vss, fss;
        vss << vertexFile.rdbuf();
        fss << fragmentFile.rdbuf();
        vertexFile.close();
        fragmentFile.close();
        vertexCode = vss.str();
        fragmentCode = fss.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    this->compile(vertexCode.c_str(), fragmentCode.c_str());
}

void Shader::compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource) {
    // vertex shader
    unsigned int s_vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(s_vert, 1, &vertexSource, NULL);
    glCompileShader(s_vert);
    checkCompileErrors(s_vert, "VERTEX");

    // fragment shader
    unsigned int s_frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(s_frag, 1, &fragmentSource, NULL);
    glCompileShader(s_frag);
    checkCompileErrors(s_frag, "FRAGMENT");

    // geometry shader
    unsigned int s_geom;
    if (geometrySource) {
        s_geom = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(s_geom, 1, &geometrySource, NULL);
        glCompileShader(s_geom);
        checkCompileErrors(s_geom, "GEOMETRY");
    }

    // 编译着色器(shader program)
    this->id = glCreateProgram();
    glAttachShader(id, s_vert);
    glAttachShader(id, s_frag);
    if (geometrySource)
        glAttachShader(id, s_geom);
    glLinkProgram(id);
    checkCompileErrors(id, "PROGRAM");

    glDeleteShader(s_vert); // 着色器链接到着色器程序对象后，可以删除着色器
    glDeleteShader(s_frag);
    if (geometrySource)
        glDeleteShader(s_geom);
}

void Shader::load(const std::string& compPath) {
    std::string compCode;
    std::ifstream compFile;
    compFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        compFile.open(compPath);
        std::stringstream css;
        css << compFile.rdbuf();
        compFile.close();
        compCode = css.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    this->compile(compCode.c_str());
}

void Shader::compile(const char *compSource) {
    // vertex shader
    unsigned int s_comp = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(s_comp, 1, &compSource, NULL);
    glCompileShader(s_comp);
    checkCompileErrors(s_comp, "COMPUTE");

    // 编译着色器(shader program)
    this->id = glCreateProgram();
    glAttachShader(id, s_comp);
    glLinkProgram(id);
    checkCompileErrors(id, "PROGRAM");

    glDeleteShader(s_comp); // 着色器链接到着色器程序对象后，可以删除着色器
}

Shader& Shader::setBool(const std::string& name, bool value) {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
    return *this;
}

Shader& Shader::setInt(const std::string& name, int value) {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
    return *this;
}

Shader& Shader::setFloat(const std::string& name, float value) {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
    return *this;
}

Shader& Shader::setVec2(const std::string& name, const glm::vec2& value) {
    glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
    return *this;
}

Shader& Shader::setVec3(const std::string& name, const glm::vec3& value) {
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
    return *this;
}

Shader& Shader::setVec4(const std::string& name, const glm::vec4& value) {
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
    return *this;
}

Shader& Shader::setVec2(const std::string& name, const float x, const float y) {
    glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
    return *this;
}

Shader& Shader::setVec3(const std::string& name, const float x, const float y, const float z) {
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
    return *this;
}

Shader& Shader::setVec4(const std::string& name, const float x, const float y, const float z, const float w) {
    glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
    return *this;
}

Shader& Shader::setMat4(const std::string& name, const glm::mat4& value) {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    return *this;
}

void Shader::checkCompileErrors(unsigned int object, std::string type) {
    int success;
    char info_log[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, sizeof(info_log), NULL, info_log);
            std::cout << "ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << info_log << std::endl;
        }
    } else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, sizeof(info_log), NULL, info_log);
            std::cout << "ERROR::Shader: Link-time error: Type: " << type << "\n"
                << info_log << std::endl;
        }
    }
}
