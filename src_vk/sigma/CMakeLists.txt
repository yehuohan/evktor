
project(sigma)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

add_library(${PROJECT_NAME} SHARED ${SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC vkt_layer)
set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX      ""
    OUTPUT_NAME "VK_LAYER_VKTOR_Sample")

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/layer)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/VK_LAYER_VKTOR_Sample.json DESTINATION ${CMAKE_INSTALL_PREFIX}/layer)
