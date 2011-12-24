cmake_minimum_required(VERSION 2.6)

include_directories("include")

set(GEOM_SRCS
    src/Point.cpp
    )

add_library(geom STATIC
    ${GEOM_SRCS}
    )
