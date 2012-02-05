#ifndef UTIL_TYPED_TYPE_INFO_H
#define UTIL_TYPED_TYPE_INFO_H

#include <algorithm>
#include <cassert>

#include "util/typed/Type.h"
#include "util/typed/TypeIdAllocator.h"

namespace util
{
    namespace typed
    {

    template<typename T>
    class TypeInfo
    {
    public:
        static const Type type;

    private:
        static std::size_t size()
        {
            return sizeof(T);
        }

        static void *construct(void *ptr)
        {
            return new(ptr)T;
        }

        static void *copyConstruct(void *ptr, const void *that)
        {
            const T *typedThat = static_cast<const T*>(that);
            return new(ptr)T(*typedThat);
        }

        static void destruct(void *ptr)
        {
            T *typedPtr = static_cast<T*>(ptr);
            typedPtr->~T();
        }

        static void copy(void *dst, const void *src)
        {
            T *typedDst = static_cast<T*>(dst);
            assert(typedDst);
            const T *typedSrc = static_cast<const T*>(src);
            assert(typedSrc);
            *typedDst = *typedSrc;
        }

        static bool equal(const void *left, const void *right)
        {
            const T *typedLeft = static_cast<const T*>(left);
            assert(typedLeft);
            const T *typedRight = static_cast<const T*>(right);
            assert(typedRight);
            return *typedLeft == *typedRight;
        }

    private:
        static Type::TypeFuncs typeFuncs;
    };

    template<typename T>
    const Type TypeInfo<T>::type(TypeIdAllocator::createId(),
        &typeFuncs);

    template<typename T>
    Type::TypeFuncs TypeInfo<T>::typeFuncs(size, construct, copyConstruct,
        destruct, copy, equal);
    }
}

#endif
