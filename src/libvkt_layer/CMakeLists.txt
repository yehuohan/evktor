
project(vkt_layer)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/generated SRC)

add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE ${SRC})
target_link_libraries(${PROJECT_NAME} INTERFACE vktor)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
if(CMAKE_SYSTEM_NAME STREQUAL Windows)
    target_compile_definitions(${PROJECT_NAME} INTERFACE "VKTLYR_API=__declspec(dllexport)")
else()
    target_compile_options(${PROJECT_NAME} INTERFACE -fvisibility=hidden)
    target_compile_definitions(${PROJECT_NAME} INTERFACE "VKTLYR_API=__attribute__((visibility(\"default\")))")
endif()
