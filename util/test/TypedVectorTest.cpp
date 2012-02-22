#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "util/typed/TypedVector.h"

namespace util
{
    namespace typed
    {
    namespace test
    {

    class TypedVectorTest: public CppUnit::TestCase
    {
        CPPUNIT_TEST_SUITE(TypedVectorTest);
        CPPUNIT_TEST(testCreate);
        CPPUNIT_TEST(testResize);
        CPPUNIT_TEST(testTypedResize);
        CPPUNIT_TEST(testCopyConstruct);
        CPPUNIT_TEST(testCopySameType);
        CPPUNIT_TEST(testCopyDiffType);
        CPPUNIT_TEST(testSetValue);
        CPPUNIT_TEST(testObjectConstruction);
        CPPUNIT_TEST_SUITE_END();

    public:
        void testCreate()
        {
            TypedVector v = TypedVector::create<int>();
            CPPUNIT_ASSERT(v.size() == 0);
        }

        void testResize()
        {
            TypedVector v = TypedVector::create<int>();
            const std::size_t size = 42;
            v.resize(size);
            CPPUNIT_ASSERT(v.size() == size);
        }

        void testTypedResize()
        {
            TypedVector v = TypedVector::create<int>();
            const std::size_t size = 42;
            v.resize<int>(size);
            CPPUNIT_ASSERT(v.size() == size);
            const int initValue = int();
            for(std::size_t i = 0; i < size; ++i)
                CPPUNIT_ASSERT(v.at<int>(i) == initValue);
        }

        void testCopyConstruct()
        {
            TypedVector v = TypedVector::create<int>();
            const std::size_t size = 42;
            v.resize(size);
            TypedVector vCopy(v);
            CPPUNIT_ASSERT(vCopy.size() == size);
        }

        void testCopySameType()
        {
            TypedVector v = TypedVector::create<int>();
            const std::size_t size = 42;
            v.resize(size);
            TypedVector vCopy = TypedVector::create<int>();
            vCopy = v;
            CPPUNIT_ASSERT(vCopy.size() == size);
        }

        void testCopyDiffType()
        {
            TypedVector v = TypedVector::create<int>();
            const std::size_t size = 42;
            v.resize(size);
            TypedVector vCopy = TypedVector::create<char>();
            vCopy = v;
            CPPUNIT_ASSERT(vCopy.size() == size);
        }

        void testSetValue()
        {
            TypedVector v = TypedVector::create<std::size_t>();
            const std::size_t size = 42;
            v.resize(size);
            for(std::size_t i = 0; i < size; ++i)
                v.at<std::size_t>(i) = i;
            for(std::size_t i = 0; i < size; ++i)
                CPPUNIT_ASSERT(v.at<std::size_t>(i) == i);
        }

        void testObjectConstruction()
        {
            const std::size_t size = 42;
            {
                TypedVector v = TypedVector::create<ObjectCounter>();
                v.resize<ObjectCounter>(size);
                CPPUNIT_ASSERT(ObjectCounter::getCount() == size);
            }
            CPPUNIT_ASSERT(ObjectCounter::getCount() == 0);
        }

    private:
        class ObjectCounter
        {
        public:
            ObjectCounter()
            {
                ++count;
            }

            ObjectCounter(const ObjectCounter&)
            {
                ++count;
            }

            ~ObjectCounter()
            {
                --count;
            }

            bool operator==(const ObjectCounter &that) const
            {
                return this == &that;
            }

        public:
            static std::size_t getCount()
            {
                return count;
            }

        private:
            static std::size_t count;
        };
    };

    std::size_t TypedVectorTest::ObjectCounter::count = 0;

    CPPUNIT_TEST_SUITE_REGISTRATION(TypedVectorTest);
    }
    }
}
