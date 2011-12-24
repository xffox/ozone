#ifndef OZONE_FPS_COUNTER_H
#define OZONE_FPS_COUNTER_H

#include "util/Time.h"

namespace ozone
{
    class FpsCounter
    {
    public:
        FpsCounter();

        unsigned int frame();

        unsigned int getFps();

        void reset();

    private:
        unsigned int calcFps(const util::Time &diff) const;

    private:
        util::Time prevTime;
        unsigned int frames;

        unsigned int fps;

    private:
        static const util::Time updateInterval;
    };
}

#endif
