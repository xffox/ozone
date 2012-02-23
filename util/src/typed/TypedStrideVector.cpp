#include "util/typed/TypedStrideVector.h"

#include <exception>
#include <cassert>

namespace util
{
namespace typed
{
TypedStrideVector::TypedStrideVector(const TypedVector &data,
    std::size_t quantum, std::size_t stride)
    :data(data), quantum(quantum), stride(stride)
{
    if(!quantum || !stride)
        throw std::exception();
}

std::size_t TypedStrideVector::size() const
{
    const std::size_t dataSize = data.size();
    const std::size_t notEmpty = !!dataSize;
    return (dataSize - notEmpty*quantum)/stride + notEmpty;
}

void TypedStrideVector::resize(std::size_t size)
{
    data.resize(calculateDataSize(size));
}

std::size_t TypedStrideVector::calculateDataSize(std::size_t size) const
{
    if(stride >= quantum)
    {
        return stride*size;
    }
    else
    {
        const std::size_t notEmpty = !!size;
        return (size - notEmpty)*stride + notEmpty*quantum;
    }
}

}
}
