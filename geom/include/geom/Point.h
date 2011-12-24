#ifndef GEOM_POINT_H
#define GEOM_POINT_H

namespace geom
{
    struct Point
    {
        Point();
        Point(double x, double y, double z);

        double x;
        double y;
        double z;
    };
}

#endif
