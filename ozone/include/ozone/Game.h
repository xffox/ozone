#ifndef OZONE_GAME_H
#define OZONE_GAME_H

#include <string>
#include <memory>

#include "ozone/GameLogic.h"
#include "ozone/RenderLogic.h"
#include "ozone/GameObjectFactory.h"

namespace ozone
{
    class Game
    {
    public:
        Game(const std::string &path);
        ~Game();

        std::auto_ptr<GameLogic> createGameLogic(GameObjectFactory *factory);
        std::auto_ptr<RenderLogic> createRenderLogic();
        std::auto_ptr<GameObjectFactory> createGameObjectFactory();

    private:
        Game(const Game&);
        Game &operator=(const Game&);
    };
}

#endif
