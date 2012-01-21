#ifndef OZONE_NATIVE_RENDER_LOGIC_H
#define OZONE_NATIVE_RENDER_LOGIC_H

#include <list>

#include "ozone/RenderLogic.h"
#include "ozone/WorldObserver.h"
#include "ozone/FpsCounter.h"

namespace render
{
    class LightDrawer;

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
    namespace object
    {
        class Light;
    }

    class NativeRenderLogic: public ozone::RenderLogic,
        public ozone::WorldObserver
    {
        typedef std::list<object::Light*> LightsContainer;

    public:
        NativeRenderLogic();

        virtual void init(render::View *view,
            ozone::WorldModel::WorldAccess *worldAccess);
        virtual void destroy(ozone::WorldModel::WorldAccess *worldAccess);
        virtual void draw(ozone::WorldModel::WorldAccess *worldAccess,
            render::Drawer *drawer);

        virtual void added(ozone::GameObject *object);
        virtual void removed(ozone::GameObject *object);
        virtual void cleared();

    private:
        NativeRenderLogic(const NativeRenderLogic&);
        NativeRenderLogic &operator=(const NativeRenderLogic&);

        void drawFps(render::Drawer *drawer);
        void initShaders();

        void initLights(ozone::WorldModel::WorldAccess *worldAccess);
        void addLight(object::Light *light);
        void removeLight(object::Light *light);
        void clearLights();

    private:
        ozone::FpsCounter fpsCounter;
        unsigned int fps;

        render::View* view;

        std::auto_ptr<render::opengl::glsl::ProgramObject> shaderProgram;
        LightsContainer lights;
    };
}

#endif
