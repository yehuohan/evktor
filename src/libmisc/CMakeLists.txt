
project(misc)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

add_library(${PROJECT_NAME} STATIC ${SRC})

set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES   "${CMAKE_CURRENT_SOURCE_DIR}"
    LINK_LIBRARIES                  "vkt_share;glfw;glm::glm;fmt::fmt;assimp::assimp")
