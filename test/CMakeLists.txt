
set(TST_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/tst_glm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tst_result.cpp)

foreach(TstFile ${TST_SRC})
    cmake_path(GET TstFile STEM TstName)
    project(${TstName})
    add_executable(${PROJECT_NAME} ${TstFile})
    target_link_libraries(${PROJECT_NAME} vktor glm::glm)
    install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
endforeach()

project(tst_glslang)
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/tst_glslang.cpp)
target_link_libraries(${PROJECT_NAME}
    glslang::glslang
    glslang::OSDependent
    glslang::MachineIndependent
    glslang::GenericCodeGen
    glslang::glslang-default-resource-limits
    glslang::OGLCompiler
    glslang::SPVRemapper
    glslang::SPIRV)
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
