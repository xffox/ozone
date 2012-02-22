#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include <iostream>

#include "util/typed/TypedStrideVector.h"

namespace util
{
    namespace typed
    {
    namespace test
    {

    class TypedStrideVectorTest: public CppUnit::TestCase
    {
        CPPUNIT_TEST_SUITE(TypedStrideVectorTest);
        CPPUNIT_TEST(testCreate);
        CPPUNIT_TEST(testCreateQuantum);
        CPPUNIT_TEST(testCreateQuantumAndStride);
        CPPUNIT_TEST(testResizeRegular);
        CPPUNIT_TEST(testResizeStrideBigger);
        CPPUNIT_TEST(testResizeStrideSmaller);
        CPPUNIT_TEST(testCopyConstruct);
        CPPUNIT_TEST(testCopy);
        CPPUNIT_TEST(testOverlap);
        CPPUNIT_TEST_SUITE_END();

    public:
        void testCreate()
        {
            TypedStrideVector v(TypedStrideVector::create<int>(1));
            CPPUNIT_ASSERT(v.size() == 0);
        }

        void testCreateQuantum()
        {
            const std::size_t quantum = 3;
            TypedStrideVector v(TypedStrideVector::create<int>(quantum));
            CPPUNIT_ASSERT(v.getQuantum() == quantum);
            CPPUNIT_ASSERT(v.getStride() == quantum);
        }

        void testCreateQuantumAndStride()
        {
            const std::size_t quantum = 3;
            const std::size_t stride = 2;
            TypedStrideVector v(TypedStrideVector::create<int>(quantum,
                    stride));
            CPPUNIT_ASSERT(v.getQuantum() == quantum);
            CPPUNIT_ASSERT(v.getStride() == stride);
        }

        void testResizeRegular()
        {
            const std::size_t quantum = 3;
            testResize(quantum, quantum);
        }

        void testResizeStrideBigger()
        {
            const std::size_t quantum = 3;
            const std::size_t stride = 5;
            testResize(quantum, stride);
        }

        void testResizeStrideSmaller()
        {
            const std::size_t quantum = 5;
            const std::size_t stride = 3;
            testResize(quantum, stride);
        }

        void testCopyConstruct()
        {
            const std::size_t quantum = 3;
            TypedStrideVector v(TypedStrideVector::create<std::size_t>(
                    quantum));
            const std::size_t size = 42;
            fill(v, quantum, size);

            TypedStrideVector vCopy(v);
            validate(v, quantum, size);
        }

        void testCopy()
        {
            const std::size_t quantum = 3;
            TypedStrideVector v(TypedStrideVector::create<std::size_t>(
                    quantum));
            const std::size_t size = 42;
            fill(v, quantum, size);

            TypedStrideVector vCopy(TypedStrideVector::create<std::size_t>(
                    quantum));
            vCopy = v;
            validate(vCopy, quantum, size);
        }

        void testOverlap()
        {
            const std::size_t quantum = 3;
            const std::size_t stride = 1;
            TypedStrideVector v(TypedStrideVector::create<std::size_t>(
                    quantum, stride));
            const std::size_t size = 42;
            fill(v, quantum, size);

            const std::size_t overlappedSize = stride*(size-1);
            for(std::size_t i = 0; i < size; ++i)
            {
                for(std::size_t j = 0; j < quantum; ++j)
                {
                    if(stride*i + j <= overlappedSize)
                    {
                        CPPUNIT_ASSERT(v.at<std::size_t>(i)[j] ==
                            quantum*(i+j));
                    }
                    else
                    {
                        CPPUNIT_ASSERT(v.at<std::size_t>(i)[j] ==
                            quantum*(size-1) + stride*i + j - overlappedSize);
                    }
                }
            }
        }

        void testResize(std::size_t quantum, std::size_t stride)
        {
            const std::size_t size1 = 42;
            const std::size_t size2 = 64;
            const std::size_t size3 = 13;
            const std::size_t size4 = 0;
            TypedStrideVector v(TypedStrideVector::create<int>(quantum,
                    stride));
            CPPUNIT_ASSERT(v.size() == 0);
            v.resize(size1);
            CPPUNIT_ASSERT(v.size() == size1);
            v.resize(size2);
            CPPUNIT_ASSERT(v.size() == size2);
            v.resize(size3);
            CPPUNIT_ASSERT(v.size() == size3);
            v.resize(size4);
            CPPUNIT_ASSERT(v.size() == size4);
        }

        void fill(TypedStrideVector &v, std::size_t quantum, std::size_t size)
        {
            v.resize(size);
            for(std::size_t i = 0; i < size; ++i)
            {
                for(std::size_t j = 0; j < quantum; ++j)
                    v.at<std::size_t>(i)[j] = quantum*i + j;
            }
        }

        void validate(const TypedStrideVector &v, std::size_t quantum,
            std::size_t size)
        {
            CPPUNIT_ASSERT(v.size() == size);
            for(std::size_t i = 0; i < size; ++i)
            {
                for(std::size_t j = 0; j < quantum; ++j)
                    CPPUNIT_ASSERT(v.at<std::size_t>(i)[j] ==
                        quantum*i + j);
            }
        }
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(TypedStrideVectorTest);
    }
    }
}
