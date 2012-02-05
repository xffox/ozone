cmake_minimum_required(VERSION 2.6)
include(FindPkgConfig)

pkg_search_module(CPPUNIT cppunit)
if(CPPUNIT_FOUND)
    set(UTIL_TEST_SRCS test.cpp
        IndexProviderTest.cpp
        TypedVectorTest.cpp
        )

    add_executable(util_test ${UTIL_TEST_SRCS})
    target_link_libraries(util_test ${CPPUNIT_LIBRARIES} util)

    get_target_property(UTIL_TEST_PATH util_test LOCATION)
    add_test(UtilTest "${UTIL_TEST_PATH}")
else(CPPUNIT_FOUND)
    message(WARNING "cppunit not found - testing is not available")
endif(CPPUNIT_FOUND)
