#ifndef OZONE_EVENT_CLIENT_H
#define OZONE_EVENT_CLIENT_H

#include "render/EventClient.h"

namespace render
{
    class KeyboardEvent;
}

namespace ozone
{
    class GameLogicExecutor;

    class EventClient: public render::EventClient
    {
    public:
        EventClient(GameLogicExecutor *executor);

        virtual void process(const render::KeyboardEvent &keyboardEvent);

    private:
        EventClient(const EventClient&);
        EventClient &operator=(const EventClient&);

    private:
        GameLogicExecutor *executor;
    };
}

#endif
