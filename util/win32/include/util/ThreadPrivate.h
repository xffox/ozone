#ifndef UTIL_THREAD_PRIVATE_H
#define UTIL_THREAD_PRIVATE_H

#include <windows.h>

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
    static DWORD WINAPI threadRoutine(LPVOID arg);

private:
    HANDLE thread;
    bool running;

    Mutex mutex;
};
}

#endif
