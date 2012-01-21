#ifndef REDNER_DRAWER_H
#define REDNER_DRAWER_H

#include <vector>
#include <string>

namespace geom
{
    class Point;
}

namespace render
{
    // TODO: translate to defines
    typedef std::vector<geom::Point> Vertices;

    class Color;
    class View;

    class Drawer
    {
    public:
        virtual ~Drawer(){}

        virtual void pushModelView() = 0;
        virtual void popModelView() = 0;
        virtual void translateModelView(float x, float y, float z) = 0;
        virtual void rotateModelView(float angleDegree,
            float x, float y, float z) = 0;

        virtual void pushProjection() = 0;
        virtual void popProjection() = 0;
        virtual void translateProjection(float x, float y, float z) = 0;
        virtual void rotateProjection(float angleDegree,
            float x, float y, float z) = 0;

        virtual void drawPoint(float x, float y,
            const Color &color) = 0;
        virtual void drawQuadrilateralsStrip(const Vertices &vertices,
                const Color &color) = 0;
        virtual void drawSphere(float r, const Color &color) = 0;
        virtual void drawText(const std::string &text, float x, float y) = 0;
    };
}

#endif
