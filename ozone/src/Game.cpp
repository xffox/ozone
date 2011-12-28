#include "ozone/Game.h"

#include "game/NativeRenderLogic.h"
#include "game/NativeGameLogic.h"
#include "game/NativeGameObjectFactory.h"

namespace ozone
{
Game::Game(const std::string&)
{
}

Game::~Game()
{
}

std::auto_ptr<GameLogic> Game::createGameLogic(GameObjectFactory *factory)
{
    return std::auto_ptr<GameLogic>(new game::NativeGameLogic(factory));
}

std::auto_ptr<RenderLogic> Game::createRenderLogic()
{
    return std::auto_ptr<RenderLogic>(new game::NativeRenderLogic);
}

std::auto_ptr<GameObjectFactory> Game::createGameObjectFactory()
{
    return std::auto_ptr<GameObjectFactory>(new game::NativeGameObjectFactory);
}
}
