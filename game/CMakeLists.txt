cmake_minimum_required(VERSION 2.6)

include_directories("include"
    "${PROJECT_SOURCE_DIR}/render/include"
    "${PROJECT_SOURCE_DIR}/util/include"
    "${PROJECT_SOURCE_DIR}/render/opengl/include"
    "${PROJECT_SOURCE_DIR}/geom/include"
    "${PROJECT_SOURCE_DIR}/ozone/include"
    )

set(GAME_SRCS
    src/Loader.cpp
    src/NativeGameLogic.cpp
    src/NativeGameObjectFactory.cpp
    src/NativeRenderLogic.cpp

    src/object/Point.cpp
    src/object/Wall.cpp
    )

add_library(game MODULE ${GAME_SRCS})

file(GLOB GAME_SHADERS ${CMAKE_CURRENT_SOURCE_DIR}/res/shader/*)

set(SHADERS_DIR "${PROJECT_BINARY_DIR}/shader")
add_custom_target(shaders_directory ALL
    ${CMAKE_COMMAND} -E make_directory "${SHADERS_DIR}"
    DEPENDS game)
foreach(SHADER_PATH IN LISTS GAME_SHADERS)
    get_filename_component(SHADER "${SHADER_PATH}" NAME)
    add_custom_target("${SHADER}" ALL
        ${CMAKE_COMMAND} -E copy_if_different "${SHADER_PATH}" "${SHADERS_DIR}"
        DEPENDS shaders_directory)
endforeach()
