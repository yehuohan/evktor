/*!
 * @brief assets manager
 */
#pragma once
#include <string>

class Assets {
public:
    static std::string dir; /**< Assets root path */

public:
    Assets() = delete;

    /*!
     * @brief Set root path of assets
     */
    static void setDir(const std::string& dir);

    static std::string getTex(const std::string& filename); 

    static std::string getFont(const std::string& filename);

    static std::string getObj(const std::string& filename);
};
