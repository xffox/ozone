#include "util/Time.h"

#include <sys/time.h>
#include <exception>

namespace util
{

// TODO: proper boundary tests
// TODO: crossplatform
// TODO: more accurate: microseconds
Time::Time()
    :seconds(0), milliseconds(0)
{
}

Time::Time(Seconds seconds, Milliseconds milliseconds)
    :seconds(seconds + milliseconds/1000),
    milliseconds(milliseconds%1000)
{
}

Time::Time(unsigned long milliseconds)
    :seconds(milliseconds/1000),
    milliseconds(milliseconds%1000)
{
}

Seconds Time::getSeconds() const
{
    return seconds;
}

Milliseconds Time::getMilliseconds() const
{
    return milliseconds;
}

Time &Time::operator+=(unsigned long milliseconds)
{
    Milliseconds newMilliseconds = milliseconds%1000;
    seconds += milliseconds/1000 + (this->milliseconds + newMilliseconds)/1000;
    this->milliseconds = (this->milliseconds + newMilliseconds)%1000;
    return *this;
}

bool Time::operator<(const Time &that) const
{
    return seconds < that.seconds ||
        ((seconds == that.seconds) && (milliseconds < that.milliseconds));
}

bool Time::operator==(const Time &that) const
{
    return seconds == that.seconds && milliseconds == that.milliseconds;
}

bool Time::operator<=(const Time &that) const
{
    return *this < that || *this == that;
}

Time Time::now()
{
    struct timeval tv = {0, 0};
    if(gettimeofday(&tv, NULL) == 0)
    {
        return Time(tv.tv_sec, tv.tv_usec/1000);
    }
    throw std::exception();
}

Time operator-(const Time &left, const Time &right)
{
    time_t borrow = left.getMilliseconds() >= right.getMilliseconds()?0:1;
    return Time(left.getSeconds()-right.getSeconds()-borrow,
            borrow*1000+left.getMilliseconds()-right.getMilliseconds());
}

}
