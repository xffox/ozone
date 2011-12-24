#ifndef UTIL_MUTEX_LOCKER_H
#define UTIL_MUTEX_LOCKER_H

namespace util
{
class Mutex;

class MutexLocker
{
public:
    MutexLocker(Mutex *mutex);
    ~MutexLocker();

private:
    MutexLocker(const MutexLocker&){}
    MutexLocker &operator=(const MutexLocker&){return *this;}

private:
    Mutex *mutex;
};
}

#endif
