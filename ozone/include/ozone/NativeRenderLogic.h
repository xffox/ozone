#ifndef OZONE_NATIVE_RENDER_LOGIC_H
#define OZONE_NATIVE_RENDER_LOGIC_H

#include "ozone/RenderLogic.h"
#include "ozone/FpsCounter.h"

namespace ozone
{
    class NativeRenderLogic: public RenderLogic
    {
    public:
        NativeRenderLogic();

        virtual void draw(WorldModel::WorldAccess *worldAccess,
            render::Drawer *drawer);

    private:
        void drawFps(render::Drawer *drawer);

    private:
        FpsCounter fpsCounter;
        unsigned int fps;
    };
}

#endif
