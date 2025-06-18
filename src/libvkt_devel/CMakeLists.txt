
project(vkt_devel)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

add_library(${PROJECT_NAME} STATIC ${SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC
    vktor
    glfw
    glm::glm
    imgui::imgui)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
