#ifndef UTIL_RUNNABLE_H
#define UTIL_RUNNABLE_H

namespace util
{
class Runnable
{
public:
    virtual ~Runnable() {}

    virtual void run() = 0;
};
}

#endif
