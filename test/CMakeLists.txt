
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
set(CASE_MAPS "static const std::map<std::string, FnCaseVoid> cases{\n")
foreach(Case ${CASES})
    list(APPEND CASE_EXTS "extern void ${Case}()\;\n")
    list(APPEND CASE_MAPS "\t{\"${Case}\", ${Case}},\n")
endforeach()
list(APPEND CASE_MAPS "}\;")

file(WRITE ${EXECUTABLE_OUTPUT_PATH}/test/tst_generated.hpp ${CASE_EXTS})
file(APPEND ${EXECUTABLE_OUTPUT_PATH}/test/tst_generated.hpp ${CASE_MAPS})

project(tst_main)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} vkt_devel vktor)
target_include_directories(${PROJECT_NAME} PUBLIC ${EXECUTABLE_OUTPUT_PATH}/test)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
