
project(omega)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/misc)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/lib SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/misc SRC)

# Borrow 'assets' and 'camera' from libvkt_devel
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libvkt_devel)
set(SRC_EXT
    ${CMAKE_CURRENT_SOURCE_DIR}/ ../libvkt_devel/assets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ ../libvkt_devel/camera.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${SRC_EXT})

target_link_libraries(${PROJECT_NAME}
    glad
    glfw
    glm::glm
    imgui::imgui
    Freetype::Freetype
    assimp::assimp
    fmt::fmt)
target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
