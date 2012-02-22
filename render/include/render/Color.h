#ifndef RENDER_COLOR_H
#define RENDER_COLOR_H

namespace render
{
    struct Color
    {
        Color()
            :r(.0f), g(.0f), b(.0f), a(.0f)
        {
        }

        Color(float r, float g, float b, float a = 1.0f)
            :r(r), g(g), b(b), a(a)
        {
        }

        float r;
        float g;
        float b;
        float a;
    };

    inline bool operator==(const Color& left, const Color& right)
    {
        return left.r == right.r && left.g == right.g && left.b == right.b &&
            left.a == right.a;
    }

    inline bool operator!=(const Color& left, const Color& right)
    {
        return !(left == right);
    }
}

#endif
