#ifndef GAME_OBJECT_WALL_H
#define GAME_OBJECT_WALL_H

#include "geom/Point.h"
#include "render/Color.h"
#include "ozone/GameObject.h"

#include <vector>

namespace game
{
    namespace object
    {
    class Wall: public ozone::GameObject
    {
        typedef std::vector<geom::Point> Vertices;

        enum IDX
        {
            BOTTOM_LEFT,
            TOP_LEFT,
            BOTTOM_RIGHT,
            TOP_RIGHT
        };

    public:
        Wall();
        Wall(const geom::Point &bottomLeft, const geom::Point &topLeft,
            const geom::Point &bottomRight, const geom::Point &topRight,
            const render::Color &color);

        virtual void draw(render::Drawer *drawer);

        void setBottomLeft(const geom::Point &p);
        void setTopLeft(const geom::Point &p);
        void setBottomRight(const geom::Point &p);
        void setTopRight(const geom::Point &p);

        const geom::Point &getBottomLeft() const;
        const geom::Point &getTopLeft() const;
        const geom::Point &getBottomRight() const;
        const geom::Point &getTopRight() const;

        void setColor(const render::Color &color);

    private:
        Vertices vertices;

        render::Color color;
    };
    }
}

#endif
