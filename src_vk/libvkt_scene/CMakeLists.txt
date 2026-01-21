
# Copy and study from `framework/scene_graph` of [Vulkan-Samples](https://github.com/KhronosGroup/Vulkan-Samples)
project(vkt_scene)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vkt_scene SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vkt_scene/components SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vkt_scene/scripts SRC)

add_library(${PROJECT_NAME} STATIC ${SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC
    vktor
    glm::glm)
target_include_directories(${PROJECT_NAME}
    PRIVATE ${Stb_INCLUDE_DIR}
    PUBLIC ${TINYGLTF_INCLUDE_DIRS}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
