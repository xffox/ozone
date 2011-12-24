#ifndef UTIL_CONDITION_PRIVATE_H
#define UTIL_CONDITION_PRIVATE_H

#include <pthread.h>

namespace util
{
    class Time;
    class Mutex;

    class ConditionPrivate
    {
    public:
        ConditionPrivate();
        ~ConditionPrivate();
 
        void wait(Mutex &mutex);
        bool timedWait(Mutex &mutex, const Time &timeout);
        void notifyOne();
        void notifyAll();

    private:
        ConditionPrivate(ConditionPrivate&){}
        ConditionPrivate& operator=(ConditionPrivate&){return *this;}

    private:
        pthread_cond_t cond;
    };
}

#endif
