#include "util/ThreadPrivate.h"

#include <cstddef>

#include "util/MutexLocker.h"
#include "util/Runnable.h"

namespace util
{
ThreadPrivate::ThreadPrivate()
    :thread(NULL), running(false)
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

    DWORD threadId;
    if(!(thread = CreateThread(NULL, 0, threadRoutine, runnable, 0,
                &threadId)))
        throw int();
    running = true;
}

void ThreadPrivate::join()
{
    MutexLocker lock(&mutex);

    if(running)
    {
        if(WaitForSingleObject(thread, INFINITE) != WAIT_OBJECT_0)
            throw int();
        CloseHandle(thread);
        thread = NULL;
        running = false;
    }
    else
    {
        throw int();
    }
}

DWORD ThreadPrivate::threadRoutine(LPVOID arg)
{
    Runnable *runnable = static_cast<Runnable*>(arg);
    if(!runnable)
        throw int();
    runnable->run();
    return 0;
}
}
