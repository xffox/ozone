#include "util/ThreadPrivate.h"

#include "util/MutexLocker.h"
#include "util/Runnable.h"

namespace util
{
ThreadPrivate::ThreadPrivate()
    :running(false)
{
}

ThreadPrivate::~ThreadPrivate()
{
}

void ThreadPrivate::run(Runnable *runnable)
{
    if(!runnable)
        throw int();

    MutexLocker lock(&mutex);

    if(running)
        throw int();

    if(pthread_create(&thread, NULL, threadRoutine, runnable) != 0)
        throw int();
    running = true;
}

void ThreadPrivate::join()
{
    MutexLocker lock(&mutex);

    if(running)
    {
        if(pthread_join(thread, NULL) != 0)
            throw int();
        running = false;
    }
    else
    {
        throw int();
    }
}

void *ThreadPrivate::threadRoutine(void *arg)
{
    Runnable *runnable = static_cast<Runnable*>(arg);
    if(!runnable)
        throw int();
    runnable->run();
    return NULL;
}
}
