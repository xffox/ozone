#include "util/ConditionPrivate.h"

#include <exception>
#include <errno.h>

#include "util/Mutex.h"
#include "util/MutexPrivate.h"
#include "util/Time.h"

namespace util
{
ConditionPrivate::ConditionPrivate()
{
    if(pthread_cond_init(&cond, NULL) != 0)
        throw std::exception();
}

ConditionPrivate::~ConditionPrivate()
{
    pthread_cond_broadcast(&cond);
    pthread_cond_destroy(&cond);
}

void ConditionPrivate::wait(Mutex &mutex)
{
    if(pthread_cond_wait(&cond, &mutex.mutexPrivate->mutex) != 0)
        throw std::exception();
}

bool ConditionPrivate::timedWait(Mutex &mutex, const Time &timeout)
{
    timespec ts = {0, 0};
    if(clock_gettime(CLOCK_REALTIME, &ts) != 0)
        throw std::exception();
    ts.tv_sec += timeout.getSeconds();
    long nanoseconds = timeout.getMilliseconds()*1000000;
    if(1000000000L - ts.tv_nsec > nanoseconds)
    {
        ts.tv_nsec += nanoseconds;
    }
    else
    {
        ts.tv_sec += 1;
        ts.tv_nsec = nanoseconds - (1000000000L - ts.tv_nsec);
    }
    int res = 0;
    if((res = pthread_cond_timedwait(&cond, &mutex.mutexPrivate->mutex,
                &ts)) == 0)
    {
        return true;
    }
    else if(res == ETIMEDOUT)
    {
        return false;
    }
    throw std::exception();
}

void ConditionPrivate::notifyOne()
{
    if(pthread_cond_signal(&cond) != 0)
        throw std::exception();
}

void ConditionPrivate::notifyAll()
{
    if(pthread_cond_broadcast(&cond) != 0)
        throw std::exception();
}

}
