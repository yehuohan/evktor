cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_ASSETS ${PROJECT_ROOT}/../assets)
set(PROJECT_SHADERS ${PROJECT_ROOT}/shaders)

set(PROJECT_BUILD_DIR ${PROJECT_ROOT}/_VOut/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BUILD_DIR}/Outputs)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BUILD_DIR}/Outputs/libs)

set(CMAKE_CXX_STANDARD 20)

if(MSVC)
    add_compile_options(/utf-8)
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(CMsg)
include(FindDeps)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/libvktor)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/libvkt_scene)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/libvkt_devel)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/libvkt_layer)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/main)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/omega)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/sigma)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)

# Install
install(FILES ${PROJECT_BUILD_DIR}/compile_commands.json DESTINATION ${PROJECT_ROOT})


# Target: tags
set_source_files_properties(tags PROPERTIES GENERATED TRUE)
add_custom_target(tags
    COMMAND ctags -R ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/deps/${VCPKG_TARGET_TRIPLET}/include
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
