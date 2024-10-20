
set(TST_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/tst_core.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tst_glm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tst_glslang.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tst_result.cpp)

foreach(TstFile ${TST_SRC})
    cmake_path(GET TstFile STEM TstName)
    project(${TstName})
    add_executable(${PROJECT_NAME} ${TstFile})
    target_link_libraries(${PROJECT_NAME} vkt_devel vktor)
    install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
endforeach()
