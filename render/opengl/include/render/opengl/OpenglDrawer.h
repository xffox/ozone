#ifndef RENDER_OPENGL_OPENGL_DRAWER_H
#define RENDER_OPENGL_OPENGL_DRAWER_H

#include "render/Drawer.h"

namespace render
{
    namespace opengl
    {
    class OpenglDrawer: public Drawer
    {
    public:
        OpenglDrawer();

        virtual void move(float x, float y, float z);
        virtual void rotate(float angleDegrees, float x, float y, float z);

        virtual void drawPoint(float x, float y, const Color &color);
        virtual void drawQuadrilateralsStrip(const Vertices &vertices,
                const Color &color);
        virtual void drawText(const std::string &text, float x, float y);

    private:
        void drawString(const std::string &str);
    };
    }
}

#endif
