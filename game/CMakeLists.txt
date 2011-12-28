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
    )

add_library(game MODULE ${GAME_SRCS})
