cmake_minimum_required(VERSION 2.6)

include_directories(
    "include"
    "${PROJECT_SOURCE_DIR}/util/include"
    "${PROJECT_SOURCE_DIR}/geom/include"
    )

set(RENDER_SRCS
    src/KeyboardEvent.cpp
    src/MouseMotionEvent.cpp
    src/VerticesData.cpp
    )

add_library(render SHARED
    ${RENDER_SRCS}
    )

add_subdirectory(opengl)
