#ifndef OZONE_NATIVE_GAME_LOGIC_H
#define OZONE_NATIVE_GAME_LOGIC_H

#include <vector>
#include <memory>

#include "ozone/GameLogic.h"

namespace render
{
    class Color;
}

namespace geom
{
    class Point;
    class Angle;
}

namespace game
{
    namespace object
    {
        class Point;
        class Wall;
    }

    class NativeGameLogic: public ozone::GameLogic
    {
        typedef std::vector<game::object::Wall*> Walls;

    public:
        NativeGameLogic(ozone::GameObjectFactory *factory);

        virtual void load(ozone::WorldModel::WorldAccess *worldAccess);
        virtual void save(ozone::WorldModel::WorldAccess *worldAccess);
        virtual void run(ozone::WorldModel::WorldAccess *worldAccess,
            ozone::Time difftime);
        virtual void process(ozone::WorldModel::WorldAccess *worldAccess,
            const render::Event &event);

    private:
        NativeGameLogic(const NativeGameLogic&);
        NativeGameLogic &operator=(const NativeGameLogic&);

        void createWall(ozone::WorldModel::WorldAccess *worldAccess,
            const geom::Point &center, float width, float height,
            const geom::Angle &yAngle, const render::Color &color);
        void createLight(ozone::WorldModel::WorldAccess *worldAccess,
            const geom::Point &position);

    private:
        ozone::GameObjectFactory *factory;

        Walls walls;

        int mouseX;
        int mouseY;
    };
}

#endif
