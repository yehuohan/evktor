
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
