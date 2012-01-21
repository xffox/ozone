#ifndef OZONE_RENDER_LOGIC_H
#define OZONE_RENDER_LOGIC_H

#include "ozone/WorldModel.h"

namespace render
{
    class View;
    class Drawer;
}

namespace ozone
{
    class RenderLogic
    {
    public:
        virtual ~RenderLogic(){}

        virtual void init(render::View *view,
            WorldModel::WorldAccess *worldAccess) = 0;
        virtual void destroy(WorldModel::WorldAccess *worldAccess) = 0;
        virtual void draw(WorldModel::WorldAccess *worldAccess,
            render::Drawer *drawer) = 0;
    };
}

#endif
