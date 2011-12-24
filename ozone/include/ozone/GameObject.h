#ifndef OZONE_GAME_OBJECT_H
#define OZONE_GAME_OBJECT_H

#include "ozone/Object.h"

namespace render
{
    class Drawer;
}

namespace ozone
{
    class GameObject: public Object
    {
    public:
        virtual void draw(render::Drawer *drawer) = 0;
    };
}

#endif
