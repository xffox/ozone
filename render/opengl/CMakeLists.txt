cmake_minimum_required(VERSION 2.6)

include_directories("include"
    "${PROJECT_SOURCE_DIR}/render/include"
    "${PROJECT_SOURCE_DIR}/util/include"
    "${PROJECT_SOURCE_DIR}/geom/include"
    )

set(OPENGL_RENDER_SRCS
    src/OpenglDrawer.cpp
    src/View.cpp
    )

if(UNIX)
    include_directories("unix/include")
    set(OPENGL_RENDER_SRCS
        ${OPENGL_RENDER_SRCS}
        unix/src/OpenglRender.cpp
        )
elseif(WIN32)
    include_directories("win32/include")
    set(OPENGL_RENDER_SRCS
        ${OPENGL_RENDER_SRCS}
        win32/src/OpenglRender.cpp
        )
else()
    message(SEND_ERROR "unsupported OS")
endif()

add_library(openglrender STATIC
    ${OPENGL_RENDER_SRCS}
    )

if(UNIX)
    target_link_libraries(openglrender render
        glut
        GLU
        util
        )
elseif(WIN32)
    target_link_libraries(openglrender render
        glu32
        opengl32 
        util
        )
else()
    message(SEND_ERROR "unsupported OS")
endif()
