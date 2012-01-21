#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include <set>
#include <exception>

#include "util/IndexProvider.h"

namespace util
{
    namespace test
    {

    class IndexProviderTest: public CppUnit::TestCase
    {
        CPPUNIT_TEST_SUITE(IndexProviderTest);
        CPPUNIT_TEST(testInit);
        CPPUNIT_TEST(testAcquire);
        CPPUNIT_TEST(testMultipleAcquire);
        CPPUNIT_TEST(testRelease);
        CPPUNIT_TEST(testMultipleRelease);
        CPPUNIT_TEST(testOverAcquire);
        CPPUNIT_TEST_EXCEPTION(testInvalidReleaseEmpty, std::exception);
        CPPUNIT_TEST_EXCEPTION(testInvalidRelease, std::exception);
        CPPUNIT_TEST_EXCEPTION(testInvalidReleaseBeyond, std::exception);
        CPPUNIT_TEST_SUITE_END();

        typedef std::set<size_t> IndexContainer;

    public:
        void testInit()
        {
            const size_t count = 1;
            IndexProvider provider(count);
            CPPUNIT_ASSERT(provider.getIndexCount() == count);
            CPPUNIT_ASSERT(provider.getUnusedIndexCount() == count);
        }

        void testAcquire()
        {
            const size_t count = 1;
            IndexProvider provider(count);
            testAcquire(provider);
            CPPUNIT_ASSERT(provider.getUnusedIndexCount() == 0);
        }

        void testMultipleAcquire()
        {
            const size_t count = 8;
            IndexProvider provider(count);
            testMultipleAcquire(provider, count);
            CPPUNIT_ASSERT(provider.getUnusedIndexCount() == 0);
        }

        void testRelease()
        {
            const size_t count = 1;
            IndexProvider provider(count);
            size_t index = testAcquire(provider);
            testRelease(provider, index);
            CPPUNIT_ASSERT(provider.getUnusedIndexCount() == count);
        }

        void testMultipleRelease()
        {
            const size_t count = 8;
            IndexProvider provider(count);
            IndexContainer indexes = testMultipleAcquire(provider, count);
            for(IndexContainer::const_iterator iter = indexes.begin(),
                endIter = indexes.end(); iter != endIter; ++iter)
            {
                testRelease(provider, *iter);
            }
            CPPUNIT_ASSERT(provider.getUnusedIndexCount() == count);
        }

        void testOverAcquire()
        {
            const size_t count = 1;
            IndexProvider provider(count);
            testAcquire(provider);
            size_t index = 0;
            bool res = provider.acquire(index);
            CPPUNIT_ASSERT(!res);
        }

        void testInvalidReleaseEmpty()
        {
            const size_t count = 1;
            IndexProvider provider(count);
            provider.release(0);
        }

        void testInvalidRelease()
        {
            const size_t count = 2;
            IndexProvider provider(count);
            IndexContainer unusedIndexes;
            for(size_t i = 0; i < count; ++i)
                unusedIndexes.insert(i);
            size_t index = testAcquire(provider);
            unusedIndexes.erase(index);
            provider.release(*unusedIndexes.begin());
        }

        void testInvalidReleaseBeyond()
        {
            const size_t count = 1;
            IndexProvider provider(count);
            provider.release(count);
        }

        size_t testAcquire(IndexProvider &provider)
        {
            size_t index = 0;
            bool res = provider.acquire(index);
            CPPUNIT_ASSERT(res);
            CPPUNIT_ASSERT(index < provider.getIndexCount());
            return index;
        }

        IndexContainer testMultipleAcquire(IndexProvider &provider, size_t count)
        {
            IndexContainer indexes;
            size_t index = 0;
            for(size_t i = 0; i < count; ++i)
            {
                index = testAcquire(provider);
                CPPUNIT_ASSERT(indexes.find(index) == indexes.end());
                indexes.insert(index);
            }
            CPPUNIT_ASSERT(indexes.size() == count);
            return indexes;
        }

        void testRelease(IndexProvider &provider, size_t index)
        {
            size_t unusedIndexCountBefore = provider.getUnusedIndexCount();
            provider.release(index);
            CPPUNIT_ASSERT(provider.getUnusedIndexCount() ==
                unusedIndexCountBefore + 1);
        }
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(IndexProviderTest);
    }
}
