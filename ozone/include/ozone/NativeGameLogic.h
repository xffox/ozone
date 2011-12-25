#ifndef OZONE_NATIVE_GAME_LOGIC_H
#define OZONE_NATIVE_GAME_LOGIC_H

#include <vector>

#include "ozone/GameLogic.h"

namespace render
{
    class Color;
}

namespace geom
{
    class Point;
}

namespace ozone
{
    namespace object
    {
        class Point;
        class Wall;
    }

    class NativeGameLogic: public GameLogic
    {
        typedef std::vector<object::Wall*> Walls;

    public:
        NativeGameLogic(GameObjectFactory *factory);

        virtual void load(WorldModel::WorldAccess *worldAccess);
        virtual void save(WorldModel::WorldAccess *worldAccess);
        virtual void run(WorldModel::WorldAccess *worldAccess,
            Time difftime);
        virtual void process(WorldModel::WorldAccess *worldAccess,
            const render::KeyboardEvent &keyboardEvent);

    private:
        NativeGameLogic(const NativeGameLogic&);
        NativeGameLogic &operator=(const NativeGameLogic&);

        void createWall(WorldModel::WorldAccess *worldAccess,
            const geom::Point &bottomLeft,
            const geom::Point &topLeft,
            const geom::Point &bottomRight,
            const geom::Point &topRight,
            const render::Color &color);

        void move(object::Wall &wall, double dist);

    private:
        GameObjectFactory *factory;

        Walls walls;
    };
}

#endif
