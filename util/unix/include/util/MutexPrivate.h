#ifndef UTIL_MUTEX_PRIVATE_H
#define UTIL_MUTEX_PRIVATE_H

#include <pthread.h>

namespace util
{
class Mutex;
class ConditionPrivate;

class MutexPrivate
{
    friend class Mutex;
    friend class ConditionPrivate;
private:
    MutexPrivate();
    ~MutexPrivate();

    void lock();
    bool tryLock();
    void unlock();

private:
    pthread_mutex_t mutex;
};
}

#endif
