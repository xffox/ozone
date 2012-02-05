#include "util/typed/TypeIdAllocator.h"

#include <limits>
#include <exception>

namespace util
{
namespace typed
{

Type::IdType TypeIdAllocator::createId()
{
    if(ids < std::numeric_limits<Type::IdType>::max())
    {
        return ids++;
    }
    throw std::exception();
}

Type::IdType TypeIdAllocator::ids = 0;

}
}
