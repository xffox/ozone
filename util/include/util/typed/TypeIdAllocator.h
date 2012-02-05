#ifndef UTIL_TYPED_TYPE_ID_ALLOCATOR_H
#define UTIL_TYPED_TYPE_ID_ALLOCATOR_H

#include "util/typed/Type.h"

namespace util
{
    namespace typed
    {

    class TypeIdAllocator
    {
        template<typename T>
        friend class TypeInfo;
    public:
        static Type::IdType getIdCount()
        {
            return ids;
        }

    private:
        static Type::IdType createId();

    private:
        static Type::IdType ids;
    };

    }
}

#endif
