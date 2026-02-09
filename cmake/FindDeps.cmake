set(DEPS_DIR ${PROJECT_ROOT}/deps/${VCPKG_TARGET_TRIPLET})
set(REPOS_DIR ${PROJECT_ROOT}/deps/repos)


# Target: Vulkan::Headers
# find_package(VulkanHeaders CONFIG REQUIRED)
add_subdirectory(${REPOS_DIR}/Vulkan-Headers)

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

# Target: tinygltf
find_path(TINYGLTF_INCLUDE_DIRS "tiny_gltf.h")

# Target: fmt::fmt, fmt::fmt-header-only
find_package(fmt CONFIG REQUIRED)

# Target: cxxopts::cxxopts
find_package(cxxopts CONFIG REQUIRED)
