#ifndef UTIL_MUTEX_PRIVATE_H
#define UTIL_MUTEX_PRIVATE_H

#include <windows.h>

namespace util
{
class MutexPrivate
{
    friend class Mutex;

private:
    MutexPrivate();
    ~MutexPrivate();

    void lock();
    void unlock();

private:
    HANDLE mutex;
};
}

#endif
