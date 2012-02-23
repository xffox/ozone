#ifndef GAME_OBJECT_WALL_H
#define GAME_OBJECT_WALL_H

#include "render/VerticesData.h"
#include "geom/Point.h"
#include "geom/Angle.h"
#include "render/Color.h"
#include "ozone/GameObject.h"

namespace game
{
    namespace object
    {
    class Wall: public ozone::GameObject
    {
        enum IDX
        {
            BOTTOM_LEFT,
            TOP_LEFT,
            BOTTOM_RIGHT,
            TOP_RIGHT
        };

    public:
        Wall();
        Wall(const geom::Point &center, float width, float height,
            const geom::Angle &yAngle, const render::Color &color);

        virtual const std::string &getType() const
        {
            return type;
        }

        virtual void draw(render::Drawer *drawer);

        void setCenter(const geom::Point &center)
        {
            this->center = center;
        }

        void setYAngle(const geom::Angle &yAngle)
        {
            this->yAngle = yAngle;
        }

        void setWidth(float width);
        void setHeight(float height);

        void setColor(const render::Color &color);

    private:
        void updateVertices();

    private:
        geom::Point center;
        float width;
        float height;
        geom::Angle yAngle;
        render::Color color;

        render::VerticesData verticesData;

    private:
        static const std::string type;
    };
    }
}

#endif
