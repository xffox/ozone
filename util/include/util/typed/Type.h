#ifndef UTIL_TYPED_TYPE_H
#define UTIL_TYPED_TYPE_H

#include <cstddef>

namespace util
{
    namespace typed
    {
    class Type
    {
    public:
        typedef size_t IdType;

        struct TypeFuncs
        {
            typedef void *(*ConstructFunc)(void*);
            typedef void *(*CopyConstructFunc)(void*, const void*);
            typedef void (*DestructFunc)(void*);
            typedef std::size_t (*SizeFunc)();
            typedef void (*CopyFunc)(void*, const void*);
            typedef bool (*EqualFunc)(const void*, const void*);

            TypeFuncs(SizeFunc size, ConstructFunc construct,
                CopyConstructFunc copyConstruct, DestructFunc destruct,
                CopyFunc copy, EqualFunc equal)
                :size(size), construct(construct),
                copyConstruct(copyConstruct), destruct(destruct), copy(copy),
                equal(equal)
            {
            }

            const SizeFunc size;
            const ConstructFunc construct;
            const CopyConstructFunc copyConstruct;
            const DestructFunc destruct;
            const CopyFunc copy;
            const EqualFunc equal;
        };

    public:
        Type(IdType id, const TypeFuncs *typeFuncs)
            :typeFuncs(typeFuncs), id(id)
        {
        }

        IdType getId() const
        {
            return id;
        }

    public:
        const TypeFuncs *typeFuncs;

    private:
        Type(const Type&);
        Type &operator=(const Type&);

    private:
        const IdType id;
    };

    inline bool operator==(const Type &left, const Type &right)
    {
        return left.getId() == right.getId();
    }

    inline bool operator!=(const Type &left, const Type &right)
    {
        return !(left == right);
    }
    }
}

#endif
