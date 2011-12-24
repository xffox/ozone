#include "util/MutexLocker.h"

#include "util/Mutex.h"

namespace util
{
MutexLocker::MutexLocker(Mutex *mutex)
    :mutex(mutex)
{
    if(!mutex)
        throw int();

    mutex->lock();
}

MutexLocker::~MutexLocker()
{
    mutex->unlock();
}

}
