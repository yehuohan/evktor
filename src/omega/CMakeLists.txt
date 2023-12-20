
# Target: glad
# https://gen.glad.sh/#generator=c&api=gl%3D4.5&profile=gl%3Dcore%2Cgles1%3Dcommon)
project(glad)
add_library(${PROJECT_NAME} INTERFACE)
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES   "${CMAKE_CURRENT_SOURCE_DIR}/glad/include"
    INTERFACE_SOURCES               "${CMAKE_CURRENT_SOURCE_DIR}/glad/src/gl.c"
    INTERFACE_COMPILE_DEFINITIONS   "GLAD_CTX_VER_MAJOR=4;GLAD_CTX_VER_MINOR=5")


project(omega)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/lib SRC_LIB)

add_executable(${PROJECT_NAME}
    ${SRC}
    ${SRC_LIB})

target_link_libraries(${PROJECT_NAME}
    misc
    glad
    glfw
    glm::glm
    imgui::imgui
    Freetype::Freetype
    assimp::assimp
    fmt::fmt)
target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
