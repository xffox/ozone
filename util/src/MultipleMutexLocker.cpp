#include "util/MultipleMutexLocker.h"

#include "util/Mutex.h"

namespace util
{

MultipleMutexLocker::MultipleMutexLocker(Mutex *a, Mutex *b)
    :a(a), b(b)
{
    if(!a || !b)
        throw int();

    Mutex *mutexes[] = {a, b};
    int pos = 0;
    while(true)
    {
        mutexes[pos]->lock();
        try
        {
            if(mutexes[!pos]->tryLock())
                return;
        }
        catch(...)
        {
            mutexes[pos]->unlock();
            throw;
        }
        mutexes[pos]->unlock();
        pos = !pos;
    }
}

MultipleMutexLocker::~MultipleMutexLocker()
{
    try
    {
        a->unlock();
    }
    catch(...)
    {
    }
    try
    {
        b->unlock();
    }
    catch(...)
    {
    }
}

}
