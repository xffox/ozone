#include "util/typed/TypedVector.h"

#include <cassert>
#include <algorithm>

namespace util
{
namespace typed
{
TypedVector::TypedVector(const Type *type)
    :type(type), data(NULL), dataSize(0), dataCapacity(0)
{
    assert(type);
}

TypedVector::TypedVector(const TypedVector &that)
    :type(that.type), data(NULL), dataSize(0), dataCapacity(0)
{
    if(that.dataSize > 0)
    {
        reserve(that.dataSize);
        copyConstructData(data, that.data, that.dataSize);
        dataSize = that.dataSize;
    }
}

TypedVector &TypedVector::operator=(const TypedVector &that)
{
    if(this == &that)
        return *this;

    if(type != that.type)
    {
        destructData(data, dataSize);
        dataSize = 0;
        retype(that.type);
        reserve(that.dataSize);
        copyConstructData(data, that.data, that.dataSize);
        dataSize = that.dataSize;
    }
    else
    {
        if(dataSize > that.dataSize)
        {
            destructData(&data[that.dataSize], dataSize - that.dataSize);
        }
        else if(dataSize < that.dataSize)
        {
            reserve(that.dataSize);
            copyConstructData(&data[dataSize], &that.data[dataSize],
                that.dataSize - dataSize);
        }
        dataSize = that.dataSize;
        if(dataSize > 0)
        {
            copyData(data, that.data, dataSize);
        }
    }

    return *this;
}

TypedVector::~TypedVector()
{
    destructData(data, dataSize);
    delete[] data;
}

void TypedVector::resize(std::size_t size)
{
    reserve(size);
    if(dataSize > size)
    {
        destructData(&data[size], dataSize - size);
    }
    else if(dataSize < size)
    {
        constructData(&data[dataSize], size - dataSize);
    }
    dataSize = size;
}

const Type::TypeFuncs &TypedVector::getTypeFuncs() const
{
    assert(type);
    assert(type->typeFuncs);
    return *type->typeFuncs;
}

void TypedVector::reserve(std::size_t size)
{
    const std::size_t elementSize = getTypeFuncs().size();
    const std::size_t newMinCapacity = elementSize*size;
    if(newMinCapacity > dataCapacity)
    {
        DataType *newData(new DataType[newMinCapacity]);
        try
        {
            copyData(newData, data, dataSize);
        }
        catch(...)
        {
            delete[] newData;
            throw;
        }
        delete[] data;
        data = newData;
        dataCapacity = newMinCapacity;
    }
}

void TypedVector::destructData(DataType *data, std::size_t dataSize)
{
    const std::size_t elementSize = getTypeFuncs().size();
    for(std::size_t i = 0; i < dataSize; ++i)
    {
        getTypeFuncs().destruct(&data[elementSize*i]);
    }
}

void TypedVector::copyData(DataType *dst, const DataType *src,
    std::size_t dataSize)
{
    const std::size_t elementSize = getTypeFuncs().size();
    for(std::size_t i = 0; i < dataSize; ++i)
    {
        getTypeFuncs().copy(&dst[elementSize*i], &src[elementSize*i]);
    }
}

void TypedVector::constructData(DataType *data, std::size_t dataSize)
{
    const std::size_t elementSize = getTypeFuncs().size();
    for(std::size_t i = 0; i < dataSize; ++i)
    {
        getTypeFuncs().construct(&data[elementSize*i]);
    }
}

void TypedVector::copyConstructData(DataType *dst, const DataType *src,
    std::size_t dataSize)
{
    const std::size_t elementSize = getTypeFuncs().size();
    for(std::size_t i = 0; i < dataSize; ++i)
    {
        getTypeFuncs().copyConstruct(&dst[elementSize*i],
            &src[elementSize*i]);
    }
}

void TypedVector::retype(const Type *type)
{
    assert(dataSize == 0);
    this->type = type;
}
}
}
