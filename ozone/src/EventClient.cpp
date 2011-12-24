#include "ozone/EventClient.h"

#include <exception>
#include <cassert>

#include "ozone/GameLogicExecutor.h"

namespace ozone
{

EventClient::EventClient(GameLogicExecutor *executor)
    :executor(executor)
{
    if(!executor)
        throw std::exception();
}

void EventClient::process(const render::KeyboardEvent &keyboardEvent)
{
    assert(executor);
    executor->process(keyboardEvent);
}

}
