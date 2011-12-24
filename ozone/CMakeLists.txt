cmake_minimum_required(VERSION 2.6)

include_directories("include"
    "${PROJECT_SOURCE_DIR}/render/include"
    "${PROJECT_SOURCE_DIR}/util/include"
    "${PROJECT_SOURCE_DIR}/render/opengl/include"
    "${PROJECT_SOURCE_DIR}/geom/include"
    )

set(OZONE_SRCS
    src/main.cpp
    src/World.cpp
    src/Object.cpp
    src/RenderClient.cpp
    src/EventClient.cpp
    src/WorldModel.cpp
    src/GameLogicExecutor.cpp
    src/FpsCounter.cpp

    src/NativeGameLogic.cpp
    src/NativeGameObjectFactory.cpp
    src/NativeRenderLogic.cpp

    src/object/Point.cpp
    src/object/Wall.cpp
    )

if(UNIX)
    include_directories("${PROJECT_SOURCE_DIR}/render/unix/include"
        "${PROJECT_SOURCE_DIR}/render/opengl/unix/include"
        )
elseif(WIN32)
    include_directories("${PROJECT_SOURCE_DIR}/render/win32/include"
        "${PROJECT_SOURCE_DIR}/render/opengl/win32/include"
        )
else()
    message(SEND_ERROR "unsupported OS")
endif()

add_executable(ozone
    ${OZONE_SRCS}
    )
target_link_libraries(ozone geom render openglrender)
