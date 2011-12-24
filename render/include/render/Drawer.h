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
    // TODO: move to defines
    typedef std::vector<geom::Point> Vertices;

    class Color;

    class Drawer
    {
    public:
        virtual ~Drawer(){}

        virtual void moveTo(float x, float y, float z) = 0;

        virtual void drawPoint(float x, float y,
            const Color &color) = 0;
        virtual void drawQuadrilateralsStrip(const Vertices &vertices,
                const Color &color) = 0;
        virtual void drawText(const std::string &text, float x, float y) = 0;
    };
}

#endif
