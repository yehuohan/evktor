
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

project(tst_main)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} vkt_devel vkt_scene vktor)
target_include_directories(${PROJECT_NAME} PUBLIC ${EXECUTABLE_OUTPUT_PATH}/test)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
