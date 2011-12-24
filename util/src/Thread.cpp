#include "util/Thread.h"

#include "util/ThreadPrivate.h"

namespace util
{
Thread::Thread()
    :threadPrivate(new ThreadPrivate())
{
}

Thread::~Thread()
{
    try
    {
        join();
    }
    catch(...)
    {
    }
    delete threadPrivate;
}

void Thread::run(Runnable *runnable)
{
    threadPrivate->run(runnable);
}

void Thread::join()
{
    threadPrivate->join();
}
}
