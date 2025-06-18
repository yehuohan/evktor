
# include(CompileShader)
# file(GLOB SHADER_VERT_SRC ${PROJECT_GLSL}/*.vert)
# file(GLOB SHADER_FRAG_SRC ${PROJECT_GLSL}/*.frag)
# add_shader_target(evktor_shader ${SHADER_VERT_SRC} ${SHADER_FRAG_SRC})

project(evktor)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} vkt_devel vkt_scene vktor)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
