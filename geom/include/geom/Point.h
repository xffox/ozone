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

    inline bool operator==(const Point& left, const Point& right)
    {
        return left.x == right.x && left.y == right.y && left.z == right.z;
    }

    inline bool operator!=(const Point& left, const Point& right)
    {
        return !(left == right);
    }
}

#endif
