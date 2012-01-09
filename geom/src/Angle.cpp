#include "geom/Angle.h"

#include <cmath>

namespace geom
{
    double Angle::getDegrees() const
    {
        return radian/M_PI*180.0;
    }

    void Angle::setDegrees(double degrees)
    {
        radian = degrees*M_PI/180.0;
    }

    bool operator==(const Angle &left, const Angle &right)
    {
        return left.getRadian() == right.getRadian();
    }

    bool operator!=(const Angle &left, const Angle &right)
    {
        return !operator==(left, right);
    }
}
