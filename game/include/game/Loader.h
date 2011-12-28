#ifndef GAME_LOADER_H
#define GAME_LOADER_H

namespace ozone
{
    struct GameModule;

    class RenderLogic;
    class GameLogic;
    class GameObjectFactory;
}

namespace game
{
    ozone::RenderLogic *createRenderLogic();
    ozone::GameLogic *createGameLogic(ozone::GameObjectFactory *factory);
    ozone::GameObjectFactory *createGameObjectFactory();
}

extern "C"
{
    ozone::GameModule *loadGameModule();
}

#endif
