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
        OpenglDrawer(View &view);

        virtual void pushModelView();
        virtual void popModelView();
        virtual void translateModelView(float x, float y, float z);
        virtual void rotateModelView(float angleDegrees,
            float x, float y, float z);

        virtual void pushProjection();
        virtual void popProjection();
        virtual void translateProjection(float x, float y, float z);
        virtual void rotateProjection(float angleDegree,
            float x, float y, float z);

        virtual void drawPoint(float x, float y, const Color &color);
        virtual void drawQuadrilateralsStrip(const Vertices &vertices,
                const Color &color);
        virtual void drawQuadrilateralsStrip(const VerticesData &data);
        virtual void drawSphere(float r, const Color &color);
        virtual void drawText(const std::string &text, float x, float y);

    private:
        void push(int mode);
        void pop(int mode);
        void translate(int mode, float x, float y, float z);
        void rotate(int mode, float angleDegrees,
            float x, float y, float z);

        void drawString(const std::string &str);

    private:
        View &view;
    };
    }
}

#endif
