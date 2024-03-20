
project(vktor)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/generated SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vktor SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vktor/core SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vktor/base SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vktor/rendering SRC)

add_library(${PROJECT_NAME} STATIC ${SRC})

target_link_libraries(${PROJECT_NAME}
    PUBLIC vkt_share
    PUBLIC Vulkan::Headers
    PUBLIC volk
    PRIVATE glslang::glslang
    PRIVATE glslang::SPIRV
    PRIVATE glslang::glslang-default-resource-limits
    PRIVATE GPUOpen::VulkanMemoryAllocator)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
