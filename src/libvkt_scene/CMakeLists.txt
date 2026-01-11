
# Copy from `framework/scene_graph` of [Vulkan-Samples](https://github.com/KhronosGroup/Vulkan-Samples)
project(vkt_scene)

# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/components SRC)
# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/scripts SRC)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/components/transform.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/node.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gltf_loader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/__impl.cpp)

add_library(${PROJECT_NAME} STATIC ${SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC
    vktor
    glm::glm)
target_include_directories(${PROJECT_NAME}
    PRIVATE ${Stb_INCLUDE_DIR}
    PUBLIC ${TINYGLTF_INCLUDE_DIRS}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
