#ifndef UTIL_INDEX_PROVIDER_H
#define UTIL_INDEX_PROVIDER_H

#include <vector>

namespace util
{
    class IndexProvider
    {
        //! The type of the container to store used indexes.
        /*!
         * There are limitations with vector<bool> - see item 18 of
         * "Effective STL: 50 specific ways to improve your use of
         * the standard template library" by Scott Meyers. But it works
         * just fine in here.
         */
        typedef std::vector<bool> IndexContainer;

    public:
        IndexProvider(size_t indexCount);

        //! Acquire unused index.
        /*!
         * \return false when there are no more unused indexes.
         */
        bool acquire(size_t &index);
        //! Release index.
        /*!
         * Raise an exception if the index is invalid or unused.
         */
        void release(size_t index);

        size_t getIndexCount() const
        {
            return indexes.size();
        }

        size_t getUnusedIndexCount() const
        {
            return getIndexCount() - usedIndexCount;
        }

    private:
        size_t usedIndexCount;
        IndexContainer indexes;
    };
}

#endif
