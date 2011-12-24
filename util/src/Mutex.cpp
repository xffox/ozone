#include "util/Mutex.h"

#include "util/MutexPrivate.h"

namespace util
{
Mutex::Mutex()
    :mutexPrivate(new MutexPrivate())
{
}

Mutex::~Mutex()
{
    delete mutexPrivate;
}

void Mutex::lock()
{
    mutexPrivate->lock();
}

bool Mutex::tryLock()
{
    return mutexPrivate->tryLock();
}

void Mutex::unlock()
{
    mutexPrivate->unlock();
}
}
