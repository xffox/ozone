#ifndef OZONE_OBJECT_POINT_H
#define OZONE_OBJECT_POINT_H

#include "ozone/GameObject.h"

namespace ozone
{
    namespace object
    {

    class Point: public GameObject
    {
    public:
        Point();
        Point(float x, float y);

        virtual void draw(render::Drawer *drawer);

    public:
        float x;
        float y;
    };

    }
}

#endif
