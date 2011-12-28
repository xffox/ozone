#ifndef OZONE_NATIVE_RENDER_LOGIC_H
#define OZONE_NATIVE_RENDER_LOGIC_H

#include "ozone/RenderLogic.h"
#include "ozone/FpsCounter.h"

namespace game
{
    class NativeRenderLogic: public ozone::RenderLogic
    {
    public:
        NativeRenderLogic();

        virtual void draw(ozone::WorldModel::WorldAccess *worldAccess,
            render::Drawer *drawer);

    private:
        void drawFps(render::Drawer *drawer);

    private:
        ozone::FpsCounter fpsCounter;
        unsigned int fps;
    };
}

#endif
