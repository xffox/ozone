cmake_minimum_required(VERSION 2.6)

include_directories("include")

set(RENDER_SRCS
    src/KeyboardEvent.cpp
    src/MouseMotionEvent.cpp
    )

add_library(render SHARED
    ${RENDER_SRCS}
    )

add_subdirectory(opengl)
