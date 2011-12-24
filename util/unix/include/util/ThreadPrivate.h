#ifndef UTIL_THREAD_PRIVATE_H
#define UTIL_THREAD_PRIVATE_H

#include <pthread.h>

#include "util/Thread.h"
#include "util/Mutex.h"

namespace util
{
class ThreadPrivate
{
public:
    ThreadPrivate();
    ~ThreadPrivate();

    void run(Runnable *runnable);
    void join();

private:
    static void *threadRoutine(void *arg);

private:
    pthread_t thread;
    bool running;

    Mutex mutex;
};
}

#endif
