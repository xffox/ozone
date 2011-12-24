#include "ozone/FpsCounter.h"

namespace ozone
{
FpsCounter::FpsCounter()
    :frames(0), fps(0)
{
}

unsigned int FpsCounter::frame()
{
    ++frames;
    const util::Time diff = util::Time::now() - prevTime;
    if(updateInterval < diff)
    {
        fps = calcFps(diff);
        prevTime = util::Time::now();
        frames = 0;
    }
    return fps;
}

unsigned int FpsCounter::getFps()
{
    return fps;
}

void FpsCounter::reset()
{
    prevTime = util::Time();
    frames = 0;
    fps = 0;
}

unsigned int FpsCounter::calcFps(const util::Time &diff) const
{
    return frames/(diff.getSeconds() +
        diff.getMilliseconds()/1000.0);
}

const util::Time FpsCounter::updateInterval(100);
}
