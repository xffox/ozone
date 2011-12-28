#ifndef GAME_MODULE_H
#define GAME_MODULE_H

namespace ozone
{
    class RenderLogic;
    class GameLogic;
    class GameObjectFactory;

    typedef GameModule *(*loadGameModuleFunc)();

    struct GameModule
    {
        ozone::RenderLogic *(*createRenderLogic)();
        ozone::GameLogic *(*createGameLogic)(ozone::GameObjectFactory*);
        ozone::GameObjectFactory *(*createGameObjectFactory)();
    };
}

#endif
