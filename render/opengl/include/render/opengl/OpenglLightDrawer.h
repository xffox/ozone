#ifndef RENDER_OPENGL_OPENGL_LIGHT_DRAWER_H
#define RENDER_OPENGL_OPENGL_LIGHT_DRAWER_H

#include <GL/gl.h>

#include "util/IndexProvider.h"
#include "render/LightDrawer.h"

namespace render
{
    namespace opengl
    {

    class OpenglLightDrawer: public LightDrawer
    {
    public:
        OpenglLightDrawer();
        virtual ~OpenglLightDrawer();

        virtual void enable();
        virtual void disable();

        virtual void setPosition(const geom::Point &position);

    private:
        GLenum light;

    private:
        static util::IndexProvider lightIndexProvider;
    };

    }
}

#endif
