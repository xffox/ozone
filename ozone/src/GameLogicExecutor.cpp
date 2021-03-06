#include "ozone/GameLogicExecutor.h"

#include <sys/time.h>
#include <exception>
#include <memory>
#include <unistd.h>

#include "ozone/Defs.h"
#include "ozone/GameLogic.h"
#include "ozone/WorldModel.h"

namespace
{
    ozone::Time toTime(const util::Time &t)
    {
        return t.getSeconds() + t.getMilliseconds()/1000.0f;
    }
}

namespace ozone
{

GameLogicExecutor::GameLogicExecutor(GameLogic *logic,
    WorldModel *model)
    :logic(logic), model(model), inputQueue()
{
    if(!logic || !model)
        throw std::exception();
}

GameLogicExecutor::~GameLogicExecutor()
{
    clearEvents();
}

void GameLogicExecutor::load()
{
    std::auto_ptr<WorldModel::WorldAccess> access(model->access());
    logic->load(access.get());
}

void GameLogicExecutor::save()
{
    std::auto_ptr<WorldModel::WorldAccess> access(model->access());
    logic->save(access.get());
}

void GameLogicExecutor::exec()
{
    load();
    loop();
    save();
}

void GameLogicExecutor::process(const render::Event &event)
{
    inputQueue.produce(event.clone().release());
}

void GameLogicExecutor::loop()
{
    util::Time nowTime;
    util::Time prevTime(util::Time::now());
    render::Event *event = NULL;
    do
    {
        {
            std::auto_ptr<WorldModel::WorldAccess> access(model->access());
            nowTime = util::Time::now();
            logic->run(access.get(), toTime(nowTime - prevTime));
            prevTime = nowTime;
        }

        if(inputQueue.timedConsume(event, iterationTime))
        {
            std::auto_ptr<WorldModel::WorldAccess> access(model->access());
            logic->process(access.get(), *event);
            delete event;
        }
    }while(true);
}

void GameLogicExecutor::clearEvents()
{
    render::Event *event = 0;
    while(inputQueue.timedConsume(event, 0))
    {
        delete event;
    }
}

const util::Time GameLogicExecutor::iterationTime(1);
}
