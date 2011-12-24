#ifndef UTIL_MULTIPLE_MUTEX_LOCKER_H
#define UTIL_MULTIPLE_MUTEX_LOCKER_H

namespace util
{
    class Mutex;

    class MultipleMutexLocker
    {
    public:
        MultipleMutexLocker(Mutex *a, Mutex *b);
        ~MultipleMutexLocker();

    private:
        MultipleMutexLocker(const MultipleMutexLocker&){}
        MultipleMutexLocker &operator=(const MultipleMutexLocker&)
        {return *this;}

    private:
        Mutex *a;
        Mutex *b;
    };
}

#endif
