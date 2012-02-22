cmake_minimum_required(VERSION 2.6)
include(FindPkgConfig)

pkg_search_module(CPPUNIT cppunit)
if(CPPUNIT_FOUND)
    set(GEOM_TEST_SRCS test.cpp
        PointTest.cpp
        )

    add_executable(geom_test ${GEOM_TEST_SRCS})
    target_link_libraries(geom_test ${CPPUNIT_LIBRARIES} geom)

    get_target_property(GEOM_TEST_PATH geom_test LOCATION)
    add_test(GeomTest "${GEOM_TEST_PATH}")
else(CPPUNIT_FOUND)
    message(WARNING "cppunit not found - testing is not available")
endif(CPPUNIT_FOUND)
