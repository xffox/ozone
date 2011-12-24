#ifndef UTIL_TIME_H
#define UTIL_TIME_H

#include <time.h>

namespace util
{
    typedef time_t Seconds;
    // enough to hold 2*999+1
    typedef unsigned short Milliseconds;

    class Time
    {
    public:
        Time();
        Time(Seconds seconds, Milliseconds milliseconds);
        Time(unsigned long milliseconds);

        Seconds getSeconds() const;
        Milliseconds getMilliseconds() const;

        Time &operator+=(unsigned long milliseconds);
        bool operator<(const Time &that) const;
        bool operator==(const Time &that) const;
        bool operator<=(const Time &that) const;

        static Time now();

    private:
        Seconds seconds;
        Milliseconds milliseconds;
    };

    Time operator-(const Time &left, const Time &right);
}

#endif
