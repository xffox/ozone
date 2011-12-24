#ifndef OZONE_NATIVE_GAME_OBJECT_FACTORY_H
#define OZONE_NATIVE_GAME_OBJECT_FACTORY_H

#include "ozone/GameObjectFactory.h"

namespace ozone
{
    class NativeGameObjectFactory: public GameObjectFactory
    {
    public:
        virtual GameObject *CreateObject(WorldModel::WorldAccess *access,
            const std::string &type);
    };
}

#endif
