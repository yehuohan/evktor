
project(vktor)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/generated SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/share SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vktor SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vktor/core/api SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vktor/core/api/exts SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vktor/core SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vktor/core/exts SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vktor/base SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vktor/rendering SRC)

# Copy and study from `framework/scene_graph` of [Vulkan-Samples](https://github.com/KhronosGroup/Vulkan-Samples)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vkt_scene SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vkt_scene/components SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vkt_scene/subpasses SRC)

add_library(${PROJECT_NAME} STATIC ${SRC})

target_link_libraries(${PROJECT_NAME}
    PUBLIC Vulkan::Headers
    PUBLIC volk
    PUBLIC glm::glm
    PRIVATE glslang::glslang
    PRIVATE glslang::SPIRV
    PRIVATE glslang::glslang-default-resource-limits
    PRIVATE GPUOpen::VulkanMemoryAllocator
    PRIVATE fmt::fmt)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(${PROJECT_NAME} PUBLIC VK_NO_PROTOTYPES) # define VK_NO_PROTOTYPES to use volk
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
