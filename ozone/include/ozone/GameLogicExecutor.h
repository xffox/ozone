#ifndef OZONE_GAME_LOGIC_EXECUTOR_H
#define OZONE_GAME_LOGIC_EXECUTOR_H

#include "ozone/Defs.h"

#include "render/Event.h"
#include "util/ProducerConsumer.h"
#include "util/Time.h"

namespace ozone
{
    class GameLogic;
    class WorldModel;

    class GameLogicExecutor
    {
    public:
        GameLogicExecutor(GameLogic *logic,
            WorldModel *model);
        ~GameLogicExecutor();

        void exec();

        void process(const render::Event &keyboardEvent);

    private:
        GameLogicExecutor(const GameLogicExecutor&);
        GameLogicExecutor &operator=(const GameLogicExecutor&);

        void load();
        void save();
        void loop();

        void clearEvents();

    private:
        GameLogic *logic;
        WorldModel *model;
        util::ProducerConsumer<render::Event*> inputQueue;

    private:
        static const util::Time iterationTime;
    };
}

#endif
