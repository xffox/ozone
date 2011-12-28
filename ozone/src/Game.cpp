#include "ozone/Game.h"

#include <dlfcn.h>
#include <exception>
#include <cassert>

#include "ozone/GameModule.h"

namespace ozone
{
Game::Game(const std::string&)
    :handle(NULL), gameModule(NULL)
{
    handle = dlopen("lib/libgame.so", RTLD_LAZY);
    if(!handle)
        throw std::exception();
    dlerror();

    loadGameModuleFunc loadGameModule = NULL;
    *reinterpret_cast<void**>(&loadGameModule) = dlsym(handle,
        "loadGameModule");
    if(dlerror() != NULL)
    {
        dlclose(handle);
        throw std::exception();
    }

    gameModule = loadGameModule();
    if(!gameModule)
    {
        dlclose(handle);
        throw std::exception();
    }
}

Game::~Game()
{
    dlclose(handle);
}

std::auto_ptr<GameLogic> Game::createGameLogic(GameObjectFactory *factory)
{
    assert(gameModule);
    return std::auto_ptr<GameLogic>(gameModule->createGameLogic(factory));
}

std::auto_ptr<RenderLogic> Game::createRenderLogic()
{
    assert(gameModule);
    return std::auto_ptr<RenderLogic>(gameModule->createRenderLogic());
}

std::auto_ptr<GameObjectFactory> Game::createGameObjectFactory()
{
    assert(gameModule);
    return std::auto_ptr<GameObjectFactory>(
        gameModule->createGameObjectFactory());
}
}
