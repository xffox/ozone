#ifndef OZONE_GAME_LOGIC_H
#define OZONE_GAME_LOGIC_H

#include "ozone/Defs.h"
#include "ozone/WorldModel.h"

namespace render
{
    class Event;
}

namespace ozone
{
    class GameObjectFactory;

    class GameLogic
    {
    public:
        GameLogic(GameObjectFactory*){}
        virtual ~GameLogic(){}

        virtual void load(WorldModel::WorldAccess *worldAccess) = 0;
        virtual void save(WorldModel::WorldAccess *worldAccess) = 0;
        virtual void run(WorldModel::WorldAccess *worldAccess,
            Time difftime) = 0;
        virtual void process(WorldModel::WorldAccess *worldAccess,
            const render::Event &event) = 0;
    };
}

#endif
