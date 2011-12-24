#include "util/MutexPrivate.h"

#include <errno.h>

namespace util
{
MutexPrivate::MutexPrivate()
{
    if(pthread_mutex_init(&mutex, NULL) != 0)
        throw int();
}

MutexPrivate::~MutexPrivate()
{
    pthread_mutex_destroy(&mutex);
}

void MutexPrivate::lock()
{
    if(pthread_mutex_lock(&mutex) != 0)
        throw int();
}

bool MutexPrivate::tryLock()
{
    int res = 0;
    if((res = pthread_mutex_trylock(&mutex)) == 0)
        return true;
    if(res == EBUSY)
        return false;
    throw int();
}

void MutexPrivate::unlock()
{
    if(pthread_mutex_unlock(&mutex) != 0)
        throw int();
}
}
