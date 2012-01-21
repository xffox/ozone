cmake_minimum_required(VERSION 2.6)

include_directories("include")

set(UTIL_SRCS
    src/Mutex.cpp
    src/MutexLocker.cpp
    src/MultipleMutexLocker.cpp
    src/Condition.cpp
    src/Thread.cpp
    src/Time.cpp
    src/IndexProvider.cpp
    )

if(UNIX)
    include_directories("unix/include")
    set(UTIL_SRCS
        ${UTIL_SRCS}
        unix/src/MutexPrivate.cpp
        unix/src/ConditionPrivate.cpp
        unix/src/ThreadPrivate.cpp
        )
elseif(WIN32)
    include_directories("win32/include")
    set(UTIL_SRCS
        ${UTIL_SRCS}
        win32/src/MutexPrivate.cpp
        win32/src/ThreadPrivate.cpp
        )
else()
    message(SEND_ERROR "unsupported OS")
endif()

add_library(util SHARED
    ${UTIL_SRCS}
    )
if(UNIX)
    target_link_libraries(util pthread rt)
endif(UNIX)

add_subdirectory(test)
