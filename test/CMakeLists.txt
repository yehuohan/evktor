
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

set(CASES)
foreach(File ${SRC})
    get_filename_component(FileName ${File} NAME)
    if(FileName MATCHES "case_.*\.cpp" )
        string(REPLACE ".cpp" "" CaseName ${FileName})
        list(APPEND CASES ${CaseName})
    endif()
endforeach()

set(CASE_EXTS)
set(CASE_MAPS "static const Map<String, FnCaseVoid> cases{\n")
foreach(Case ${CASES})
    string(APPEND CASE_EXTS "extern void ${Case}();\n")
    string(APPEND CASE_MAPS "\t{\"${Case}\", ${Case}},\n")
endforeach()
string(APPEND CASE_MAPS "};\n")
string(MD5 HPP_HASH "${CASE_EXTS}${CASE_MAPS}") # Must use quote to keep ";"

set(HPP ${EXECUTABLE_OUTPUT_PATH}/test/tst_generated.hpp)
set(HPP_HASH_OLD "")
if(EXISTS ${HPP})
    file(READ ${HPP} HPP_DATA)
    string(MD5 HPP_HASH_OLD "${HPP_DATA}")
endif()
if(NOT HPP_HASH STREQUAL HPP_HASH_OLD)
    file(WRITE ${HPP} "${CASE_EXTS}${CASE_MAPS}")
endif()

# include(CompileShader)
# file(GLOB SHADER_SRC
#     ${PROJECT_SHADERS}/test/*.slang
#     ${PROJECT_SHADERS}/test/*.comp
#     ${PROJECT_SHADERS}/test/*.vert
#     ${PROJECT_SHADERS}/test/*.frag)
# add_shader_target(tst_shader ${SHADER_SRC})

project(tst_main)

include_directories(${PROJECT_ROOT}/src_vk/evktor/devel)
set(SRC_EXT ${PROJECT_ROOT}/src_vk/evktor/devel/assets.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${SRC_EXT})
target_link_libraries(${PROJECT_NAME} vktor)
target_include_directories(${PROJECT_NAME} PUBLIC ${EXECUTABLE_OUTPUT_PATH}/test)
target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME}
    PRIVATE ${Stb_INCLUDE_DIR}
    PRIVATE ${TINYGLTF_INCLUDE_DIRS})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
