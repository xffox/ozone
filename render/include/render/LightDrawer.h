#ifndef RENDER_LIGHT_DRAWER_H
#define RENDER_LIGHT_DRAWER_H

namespace geom
{
    class Point;
}

namespace render
{
    class LightDrawer
    {
    public:
        virtual ~LightDrawer(){}

        virtual void enable() = 0;
        virtual void disable() = 0;

        virtual void setPosition(const geom::Point &position) = 0;
    };
}

#endif
