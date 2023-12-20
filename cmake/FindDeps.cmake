set(DEPS_DIR ${PROJECT_ROOT}/deps/${VCPKG_TARGET_TRIPLET})
set(REPOS_DIR ${PROJECT_ROOT}/deps/repos)


# Target: Vulkan::Headers
find_package(VulkanHeaders CONFIG REQUIRED)

# Target: volk
# Prefer Vulkan-Headers than Vulkan SDK
set(VULKAN_HEADERS_INSTALL_DIR ${DEPS_DIR})
if(CMAKE_SYSTEM_NAME STREQUAL Windows)
    set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_WIN32_KHR)
elseif(CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_XLIB_KHR)
elseif(CMAKE_SYSTEM_NAME STREQUAL Android)
    set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_ANDROID_KHR)
elseif(CMAKE_SYSTEM_NAME STREQUAL Darwin)
    set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_MACOS_MVK)
endif()
cmsg(INFO "VOLK_STATIC_DEFINES = ${VOLK_STATIC_DEFINES}")
add_subdirectory(${REPOS_DIR}/volk)

# Target: glslang::glslang
find_package(glslang CONFIG REQUIRED)
set(glslang_glslangValidator ${DEPS_DIR}/tools/glslang/glslangValidator)

# Target: GPUOpen::VulkanMemoryAllocator
find_package(VulkanMemoryAllocator CONFIG REQUIRED)
# Fetch Vulkan function with volk loader for vma
target_compile_definitions(GPUOpen::VulkanMemoryAllocator
    INTERFACE VMA_STATIC_VULKAN_FUNCTIONS=0
    INTERFACE VMA_DYNAMIC_VULKAN_FUNCTIONS=0)

# Target: glfw
find_package(glfw3 CONFIG REQUIRED)

# Target: glm::glm
find_package(glm CONFIG REQUIRED)

# Target: ${Stb_INCLUDE_DIR}
find_package(Stb REQUIRED)

# Target: imgui::imgui
find_package(imgui CONFIG REQUIRED)

# Target: Freetype::Freetype
find_package(Freetype REQUIRED)

# Target: assimp::assimp
find_package(assimp CONFIG REQUIRED)
install(IMPORTED_RUNTIME_ARTIFACTS assimp::assimp RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})

# Target: fmt::fmt, fmt::fmt-header-only
find_package(fmt CONFIG REQUIRED)
