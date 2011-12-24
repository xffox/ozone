#ifndef OZONE_RENDER_CLIENT_H
#define OZONE_RENDER_CLIENT_H

#include "render/Client.h"

namespace ozone
{
    class WorldModel;
    class RenderLogic;

    class RenderClient: public render::Client
    {
    public:
        RenderClient(WorldModel *model, RenderLogic *renderLogic);

        virtual void draw(render::Drawer *drawer);

    private:
        WorldModel *model;
        RenderLogic *renderLogic;
    };
}

#endif
