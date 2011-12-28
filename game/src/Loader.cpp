#include "game/Loader.h"

#include "ozone/GameModule.h"
#include "game/NativeGameLogic.h"
#include "game/NativeRenderLogic.h"
#include "game/NativeGameObjectFactory.h"

namespace
{
ozone::GameModule gameModule;
}

namespace game
{
ozone::RenderLogic *createRenderLogic()
{
    return new game::NativeRenderLogic;
}

ozone::GameLogic *createGameLogic(ozone::GameObjectFactory *factory)
{
    return new game::NativeGameLogic(factory);
}

ozone::GameObjectFactory *createGameObjectFactory()
{
    return new game::NativeGameObjectFactory();
}
}

ozone::GameModule *loadGameModule()
{
    gameModule.createRenderLogic = game::createRenderLogic;
    gameModule.createGameLogic = game::createGameLogic;
    gameModule.createGameObjectFactory = game::createGameObjectFactory;
    return &gameModule;
}
