#ifndef OZONE_GAME_LOGIC_EXECUTOR_H
#define OZONE_GAME_LOGIC_EXECUTOR_H

#include "ozone/Defs.h"

#include "render/KeyboardEvent.h"
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

        void exec();

        void process(const render::KeyboardEvent &keyboardEvent);

    private:
        void load();
        void save();
        void loop();

    private:
        GameLogic *logic;
        WorldModel *model;
        util::ProducerConsumer<render::KeyboardEvent> inputQueue;

    private:
        static const util::Time iterationTime;
    };
}

#endif
