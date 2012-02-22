#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "geom/Point.h"

namespace geom
{
    namespace test
    {
    class PointTest: public CppUnit::TestCase
    {
        CPPUNIT_TEST_SUITE(PointTest);
        CPPUNIT_TEST(testDefaultConstruct);
        CPPUNIT_TEST(testConstruct);
        CPPUNIT_TEST(testDefaultEqual);
        CPPUNIT_TEST(testEqual);
        CPPUNIT_TEST(testCopy);
        CPPUNIT_TEST_SUITE_END();

    public:
        void testDefaultConstruct()
        {
            Point a;
            CPPUNIT_ASSERT(a.x == 0);
            CPPUNIT_ASSERT(a.y == 0);
            CPPUNIT_ASSERT(a.z == 0);
        }

        void testConstruct()
        {
            Point a(1.0f, 2.0f, 3.0f);
            CPPUNIT_ASSERT(a.x == 1.0f);
            CPPUNIT_ASSERT(a.y == 2.0f);
            CPPUNIT_ASSERT(a.z == 3.0f);
        }

        void testDefaultEqual()
        {
            Point a;
            Point b;
            CPPUNIT_ASSERT(a == b);
        }

        void testEqual()
        {
            Point a(1.0f, 2.0f, 3.0f);
            Point b(1.0f, 2.0f, 3.0f);
            CPPUNIT_ASSERT(a == b);
        }

        void testCopy()
        {
            Point a(1.0f, 2.0f, 3.0f);
            Point b;
            CPPUNIT_ASSERT(a.x != b.x);
            CPPUNIT_ASSERT(a.y != b.y);
            CPPUNIT_ASSERT(a.z != b.z);
            b = a;
            CPPUNIT_ASSERT(a.x == b.x);
            CPPUNIT_ASSERT(a.y == b.y);
            CPPUNIT_ASSERT(a.z == b.z);
        }
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(PointTest);
    }
}
