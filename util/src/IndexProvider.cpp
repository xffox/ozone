#include "util/IndexProvider.h"

#include <algorithm>
#include <exception>
#include <cassert>

namespace util
{

IndexProvider::IndexProvider(size_t indexCount)
    :usedIndexCount(0), indexes(indexCount)
{
}

bool IndexProvider::acquire(size_t &index)
{
    if(usedIndexCount < indexes.size())
    {
        IndexContainer::iterator usedIndexIter =
            std::find(indexes.begin(), indexes.end(), false);
        assert(usedIndexIter != indexes.end());
        *usedIndexIter = true;
        ++usedIndexCount;
        index = usedIndexIter - indexes.begin();
        return true;
    }
    return false;
}

void IndexProvider::release(size_t index)
{
    if(index < indexes.size() && indexes[index])
    {
        indexes[index] = false;
        --usedIndexCount;
    }
    else
    {
        throw std::exception();
    }
}

}
