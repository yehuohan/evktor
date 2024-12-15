
project(vktor)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/generated SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/share SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vktor SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vktor/core SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vktor/core/api SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vktor/base SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vktor/rendering SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/scene SRC)

add_library(${PROJECT_NAME} STATIC ${SRC})

target_link_libraries(${PROJECT_NAME}
    PUBLIC Vulkan::Headers
    PUBLIC volk
    PRIVATE glslang::glslang
    PRIVATE glslang::SPIRV
    PRIVATE glslang::glslang-default-resource-limits
    PRIVATE GPUOpen::VulkanMemoryAllocator
    PRIVATE fmt::fmt)
target_include_directories(${PROJECT_NAME}
    PRIVATE ${Stb_INCLUDE_DIR}
    PUBLIC ${TINYGLTF_INCLUDE_DIRS}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# define VK_NO_PROTOTYPES to use volk
target_compile_definitions(${PROJECT_NAME} PUBLIC VK_NO_PROTOTYPES)
