#ifndef RENDER_COLOR_H
#define RENDER_COLOR_H

namespace render
{
    struct Color
    {
        Color(float r, float g, float b, float a = 1.0f)
            :r(r), g(g), b(b), a(a)
        {
        }

        float r;
        float g;
        float b;
        float a;
    };
}

#endif
