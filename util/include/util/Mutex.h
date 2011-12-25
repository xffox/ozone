#ifndef UTIL_MUTEX_H
#define UTIL_MUTEX_H

namespace util
{
class MutexPrivate;
class ConditionPrivate;

class Mutex
{
    friend class ConditionPrivate;
public:
    Mutex();
    ~Mutex();

    void lock();
    bool tryLock();
    void unlock();

private:
    Mutex(const Mutex&);
    Mutex &operator=(const Mutex&);

private:
    MutexPrivate *mutexPrivate;
};
}

#endif
