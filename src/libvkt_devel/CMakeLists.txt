
project(vkt_devel)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

add_library(${PROJECT_NAME} STATIC ${SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC
    vktor
    glfw
    glm::glm
    imgui::imgui
    Freetype::Freetype
    fmt::fmt)
target_include_directories(${PROJECT_NAME}
    PRIVATE ${Stb_INCLUDE_DIR}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
