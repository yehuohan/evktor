#pragma once
#include "share/share.hpp"
#include <string>

NAMESPACE_BEGIN(vktdev)

class Assets {
public:
    static std::string assets;
    static std::string shader;

public:
    Assets() = delete;

    static void setDirs(const std::string& assets_dir, const std::string& shader_dir = ".");
    static std::string getTex(const std::string& filename);
    static std::string getFont(const std::string& filename);
    static std::string getObj(const std::string& filename);
    static std::string getShader(const std::string& filename);
};

NAMESPACE_END(vktdev)
