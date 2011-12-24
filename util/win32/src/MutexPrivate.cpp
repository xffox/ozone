#include "util/MutexPrivate.h"

namespace util
{
MutexPrivate::MutexPrivate()
    :mutex(NULL)
{
    if(!(mutex = CreateMutex(NULL, FALSE, NULL)))
        throw int();
}

MutexPrivate::~MutexPrivate()
{
    CloseHandle(mutex);
    mutex = NULL;
}

void MutexPrivate::lock()
{
    if(WaitForSingleObject(mutex, INFINITE) != WAIT_OBJECT_0)
        throw int();
}

void MutexPrivate::unlock()
{
    if(!ReleaseMutex(mutex))
        throw int();
}
}
