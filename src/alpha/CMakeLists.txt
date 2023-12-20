
# include(CompileShader)
# file(GLOB SHADER_VERT_SRC ${PROJECT_GLSL}/alpha/*.vert)
# file(GLOB SHADER_FRAG_SRC ${PROJECT_GLSL}/alpha/*.frag)
# add_shader_target(alpha_shader ${SHADER_VERT_SRC} ${SHADER_FRAG_SRC})


project(alpha)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME}
    vktor
    misc
    glfw
    glm::glm
    imgui::imgui
    Freetype::Freetype
    assimp::assimp)
target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
