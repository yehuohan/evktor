
# include(CompileShader)
# file(GLOB SHADER_SRC
#     ${PROJECT_SHADERS}/*.slang
#     ${PROJECT_SHADERS}/*.comp
#     ${PROJECT_SHADERS}/*.vert
#     ${PROJECT_SHADERS}/*.frag)
# add_shader_target(evktor_shader ${SHADER_SRC})

project(evktor)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/devel SRC)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME}
    cxxopts::cxxopts
    glfw
    imgui::imgui
    vktor)
target_include_directories(${PROJECT_NAME}
    PRIVATE ${Stb_INCLUDE_DIR}
    PRIVATE ${TINYGLTF_INCLUDE_DIRS})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
