
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

project(tst_main)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} vkt_devel vktor)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
