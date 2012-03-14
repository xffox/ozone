cmake_minimum_required(VERSION 2.6)

project(ozone)

include(CTest)

set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

if(UNIX)
    set(WARN_FLAGS "-Wall -Wextra -Weffc++ -pedantic")
    set(DEBUG_FLAGS "")
    # GCC coverage flag: --coverage
    set(INSTRUMENTATION_FLAGS "")
elseif(WIN32)
    # "-static" - make it static to run without libs
    # "-Wl,--subsystem,windows" - make window application
    # TODO: WIN32 in add_executable()
    set(ADD_FLAGS "-static -Wl,--subsystem,windows")
endif()

set(CMAKE_CXX_FLAGS
    "${WARN_FLAGS} ${DEBUG_FLAGS} ${ADD_FLAGS} ${INSTRUMENTATION_FLAGS} ${CMAKE_CXX_FLAGS}")
set(LINK_FLAGS "${INSTRUMENTATION_FLAGS} ${LINK_FLAGS}")

add_subdirectory(util)
add_subdirectory(render)
add_subdirectory(geom)
add_subdirectory(game)
add_subdirectory(ozone)
