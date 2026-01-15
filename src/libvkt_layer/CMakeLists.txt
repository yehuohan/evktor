
project(vkt_layer)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/generated SRC)

add_library(${PROJECT_NAME} STATIC ${SRC})
target_link_libraries(${PROJECT_NAME} PUBLIC vktor)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
if(CMAKE_SYSTEM_NAME STREQUAL Windows)
    target_compile_definitions(${PROJECT_NAME} PUBLIC "VKTLYR_API=__declspec(dllexport)")
else()
    target_compile_options(${PROJECT_NAME} PUBLIC -fvisibility=hidden)
    target_compile_definitions(${PROJECT_NAME} PUBLIC "VKTLYR_API=__attribute__((visibility(\"default\")))")
endif()
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
