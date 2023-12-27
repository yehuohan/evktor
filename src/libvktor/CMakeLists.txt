
project(vktor)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/common SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vktor SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vktor/generated SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vktor/core SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/vktor/base SRC)

add_library(${PROJECT_NAME} STATIC ${SRC})

set(LINKED_LIBS
    Vulkan::Headers
    volk
    glslang::glslang
    glslang::SPIRV
    glslang::glslang-default-resource-limits
    GPUOpen::VulkanMemoryAllocator
    fmt::fmt)
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES   "${CMAKE_CURRENT_SOURCE_DIR}"
    LINK_LIBRARIES                  "${LINKED_LIBS}"
    INTERFACE_LINK_LIBRARIES        "${LINKED_LIBS}")
