#ifndef UTIL_TYPED_TYPED_STRIDE_VECTOR_H
#define UTIL_TYPED_TYPED_STRIDE_VECTOR_H

#include "util/typed/TypedVector.h"

namespace util
{
    namespace typed
    {
    class Type;

    class TypedStrideVector
    {
    public:
        template<typename T>
        class Reference
        {
            friend class TypedStrideVector;

        public:
            T &operator[](std::size_t index);
            const T &operator[](std::size_t index) const;

        private:
            Reference(TypedStrideVector &datum, std::size_t index);

        private:
            TypedStrideVector &datum;
            const std::size_t datumIndex;
        };

        template<typename T>
        class ConstReference
        {
            friend class TypedStrideVector;

        public:
            const T &operator[](std::size_t index);
            const T &operator[](std::size_t index) const;

        private:
            ConstReference(const TypedStrideVector &datum, std::size_t index);

        private:
            const TypedStrideVector &datum;
            const std::size_t datumIndex;
        };

    public:
        std::size_t size() const;

        std::size_t getStride() const
        {
            return stride;
        }

        std::size_t getQuantum() const
        {
            return quantum;
        }

        template<typename T>
        Reference<T> at(std::size_t index);
        template<typename T>
        ConstReference<T> at(std::size_t index) const;

        void resize(std::size_t size);

    public:
        template<typename T>
        static TypedStrideVector create(std::size_t quantum);
        template<typename T>
        static TypedStrideVector create(std::size_t quantum,
            std::size_t stride);

    private:
        TypedStrideVector(const TypedVector &data, std::size_t quantum,
            std::size_t stride);

    private:
        TypedVector data;
        std::size_t quantum;
        std::size_t stride;
    };

    template<typename T>
    TypedStrideVector::Reference<T>::Reference(
        TypedStrideVector &datum, std::size_t index)
        :datum(datum), datumIndex(datum.stride*index)
    {
        if(index >= datum.size())
            throw std::exception();
    }

    template<typename T>
    T &TypedStrideVector::Reference<T>::operator[](std::size_t index)
    {
        return this->datum.data.at<T>(this->datumIndex + index);
    }

    template<typename T>
    const T &TypedStrideVector::Reference<T>::operator[](
        std::size_t index) const
    {
        return const_cast<Reference<T>*>(this)->operator[](index);
    }

    template<typename T>
    TypedStrideVector::ConstReference<T>::ConstReference(
        const TypedStrideVector &datum, std::size_t index)
        :datum(datum), datumIndex(datum.stride*index)
    {
        if(index >= datum.size())
            throw std::exception();
    }

    template<typename T>
    const T &TypedStrideVector::ConstReference<T>::operator[](
        std::size_t index)
    {
        return this->datum.data.at<T>(this->datumIndex + index);
    }

    template<typename T>
    const T &TypedStrideVector::ConstReference<T>::operator[](
        std::size_t index) const
    {
        return const_cast<Reference<T>*>(this)->operator[](index);
    }

    template<typename T>
    TypedStrideVector::Reference<T> TypedStrideVector::at(std::size_t index)
    {
        return Reference<T>(*this, index);
    }

    template<typename T>
    TypedStrideVector::ConstReference<T> TypedStrideVector::at(
        std::size_t index) const
    {
        return ConstReference<T>(*this, index);
    }

    template<typename T>
    TypedStrideVector TypedStrideVector::create(std::size_t quantum)
    {
        return TypedStrideVector(TypedVector::create<T>(), quantum, quantum);
    }

    template<typename T>
    TypedStrideVector TypedStrideVector::create(std::size_t quantum,
        std::size_t stride)
    {
        return TypedStrideVector(TypedVector::create<T>(), quantum, stride);
    }

    }
}

#endif
