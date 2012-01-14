#ifndef OZONE_NATIVE_RENDER_LOGIC_H
#define OZONE_NATIVE_RENDER_LOGIC_H

#include "ozone/RenderLogic.h"
#include "ozone/FpsCounter.h"

namespace render
{
    namespace opengl
    {
        namespace glsl
        {
            class ProgramObject;
        }
    }
}

namespace game
{
    class NativeRenderLogic: public ozone::RenderLogic
    {
    public:
        NativeRenderLogic();

        virtual void init();
        virtual void destroy();
        virtual void draw(ozone::WorldModel::WorldAccess *worldAccess,
            render::Drawer *drawer);

    private:
        void drawFps(render::Drawer *drawer);
        void initShaders();

    private:
        ozone::FpsCounter fpsCounter;
        unsigned int fps;

        std::auto_ptr<render::opengl::glsl::ProgramObject> shaderProgram;
    };
}

#endif
