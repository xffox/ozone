#ifndef OZONE_RENDER_CLIENT_H
#define OZONE_RENDER_CLIENT_H

#include "render/Client.h"

namespace render
{
    class View;
}

namespace ozone
{
    class WorldModel;
    class RenderLogic;

    class RenderClient: public render::Client
    {
    public:
        RenderClient(WorldModel *model, RenderLogic *renderLogic);

        virtual void init(render::View *view);
        virtual void destroy();
        virtual void draw(render::Drawer *drawer);

    private:
        RenderClient(const RenderClient&);
        RenderClient &operator=(const RenderClient&);

    private:
        WorldModel *model;
        RenderLogic *renderLogic;
    };
}

#endif
