#ifndef UTIL_THREAD_H
#define UTIL_THREAD_H

namespace util
{
class ThreadPrivate;
class Runnable;

class Thread
{
public:
    Thread();
    ~Thread();

    void run(Runnable *runnable);
    void join();

private:
    ThreadPrivate *threadPrivate;
};
}

#endif
