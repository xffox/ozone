#ifndef OZONE_DEFS_H
#define OZONE_DEFS_H

#include <vector>

#include "geom/Angle.h"

namespace ozone
{
    typedef float Time;

    // TODO: remove this
    typedef std::vector<float> ViewPos;
    typedef std::vector<geom::Angle> ViewAngle;
}

#endif
