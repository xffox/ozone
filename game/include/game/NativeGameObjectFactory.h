#ifndef OZONE_NATIVE_GAME_OBJECT_FACTORY_H
#define OZONE_NATIVE_GAME_OBJECT_FACTORY_H

#include "ozone/GameObjectFactory.h"

namespace game
{
    class NativeGameObjectFactory: public ozone::GameObjectFactory
    {
    public:
        virtual ozone::GameObject *CreateObject(
            ozone::WorldModel::WorldAccess *access,
            const std::string &type);
    };
}

#endif
