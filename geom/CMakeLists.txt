cmake_minimum_required(VERSION 2.6)

include_directories("include")

set(GEOM_SRCS
    src/Point.cpp
    src/Angle.cpp
    )

add_library(geom SHARED
    ${GEOM_SRCS}
    )

add_subdirectory(test)
