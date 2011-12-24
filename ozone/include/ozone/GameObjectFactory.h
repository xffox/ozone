#ifndef OZONE_GAME_OBJECT_FACTORY_H
#define OZONE_GAME_OBJECT_FACTORY_H

#include <string>

#include "ozone/WorldModel.h"

namespace ozone
{
    class GameObject;

    class GameObjectFactory
    {
    public:
        virtual ~GameObjectFactory(){}

        virtual GameObject *CreateObject(WorldModel::WorldAccess *access,
            const std::string &type) = 0;
    };
}

#endif
