cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_THIS ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_ROOT ${PROJECT_THIS}/../)
set(DEPS_DIR ${PROJECT_THIS}/deps/${VCPKG_TARGET_TRIPLET})
set(REPOS_DIR ${PROJECT_THIS}/deps/repos)

set(PROJECT_BUILD_DIR ${PROJECT_THIS}/_VOut/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BUILD_DIR}/Outputs)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BUILD_DIR}/Outputs/libs)

set(CMAKE_CXX_STANDARD 20)

if(MSVC)
    add_compile_options(/utf-8)
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_ROOT}/cmake)
include(CMsg)

# Target: glad
project(glad)
add_library(glad INTERFACE)
set_target_properties(glad PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES   "${REPOS_DIR}/glad/include"
    INTERFACE_SOURCES               "${REPOS_DIR}/glad/src/gl.c"
    INTERFACE_COMPILE_DEFINITIONS   "GLAD_CTX_VER_MAJOR=4;GLAD_CTX_VER_MINOR=5")

# Target: glfw
find_package(glfw3 CONFIG REQUIRED)

# Target: glm::glm
find_package(glm CONFIG REQUIRED)

# Target: ${Stb_INCLUDE_DIR}
find_package(Stb REQUIRED)

# Target: imgui::imgui
find_package(imgui CONFIG REQUIRED)

# Target: Freetype::Freetype
find_package(Freetype REQUIRED)

# Target: assimp::assimp
find_package(assimp CONFIG REQUIRED)
install(IMPORTED_RUNTIME_ARTIFACTS assimp::assimp RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})

# Target: fmt::fmt, fmt::fmt-header-only
find_package(fmt CONFIG REQUIRED)

# Target: omega
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/omega)

# Install
install(FILES ${PROJECT_BUILD_DIR}/compile_commands.json DESTINATION ${PROJECT_THIS})
