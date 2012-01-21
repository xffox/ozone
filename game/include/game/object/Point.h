#ifndef GAME_OBJECT_POINT_H
#define GAME_OBJECT_POINT_H

#include "ozone/GameObject.h"

namespace game
{
    namespace object
    {

    class Point: public ozone::GameObject
    {
    public:
        Point();
        Point(float x, float y);

        virtual const std::string &getType() const
        {
            return type;
        }

        virtual void draw(render::Drawer *drawer);

    public:
        float x;
        float y;

    private:
        static const std::string type;
    };

    }
}

#endif
