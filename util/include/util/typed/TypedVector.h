#ifndef UTIL_TYPED_TYPED_VECTOR_H
#define UTIL_TYPED_TYPED_VECTOR_H

#include <cassert>
#include <exception>

#include "util/typed/Type.h"
#include "util/typed/TypeInfo.h"

namespace util
{
    namespace typed
    {
    /*!
     * Vector container that represents single object type
     * but can be parametrized with contained type.
     * Data is stored continuously in the memory.
     */
    class TypedVector
    {
        typedef unsigned char DataType;

    public:
        TypedVector(const TypedVector &that);
        TypedVector &operator=(const TypedVector &that);

        ~TypedVector();

        //! Create typed vector
        /*!
         * No direct creation allowed, use this static creator.
         */
        template<typename T>
        static TypedVector create();

        //! Return element at index.
        /*!
         * \exception std::exception index is out of range.
         */
        template<typename T>
        T &at(std::size_t index);
        template<typename T>
        const T &at(std::size_t index) const;

        //! Change size to specified.
        /*!
         * Extra items will be default-constructed.
         */
        void resize(std::size_t size);
        //! Change size to specified using value to construct extra items.
        template<typename T>
        void resize(std::size_t size, const T &val = T());

        std::size_t size() const
        {
            return dataSize;
        }

        //! Reserve at least specified capacity.
        /*!
         * Capacity can only be increased.
         */
        void reserve(std::size_t size);

    private:
        TypedVector(const Type *type);

        template<typename T>
        void validateType();

        const Type::TypeFuncs &getTypeFuncs() const;

        void constructData(DataType *data, std::size_t dataSize);
        void copyConstructData(DataType *dst, const DataType *src,
            std::size_t dataSize);
        void copyData(DataType *dst, const DataType *src,
            std::size_t dataSize);
        void destructData(DataType *data, std::size_t dataSize);
        void retype(const Type *type);

    private:
        const Type *type;

        DataType *data;
        std::size_t dataSize;
        std::size_t dataCapacity;
    };

    template<typename T>
    TypedVector TypedVector::create()
    {
        return TypedVector(&TypeInfo<T>::type);
    }

    template<typename T>
    T &TypedVector::at(std::size_t index)
    {
        validateType<T>();
        if(index >= dataSize)
            throw std::exception();
        T *typedData = reinterpret_cast<T*>(data);
        assert(typedData);
        return typedData[index];
    }

    template<typename T>
    const T &TypedVector::at(std::size_t index) const
    {
        return const_cast<TypedVector*>(this)->at<T>(index);
    }

    template<typename T>
    void TypedVector::resize(std::size_t size, const T &val)
    {
        validateType<T>();
        std::size_t uninitedBegin = std::min(dataSize, size);
        resize(size);
        assert(dataSize == size);
        while(uninitedBegin < dataSize)
        {
            at<T>(uninitedBegin++) = val;
        }
    }

    template<typename T>
    void TypedVector::validateType()
    {
        if(TypeInfo<T>::type != *type)
            throw std::exception();
    }
    }
}

#endif
