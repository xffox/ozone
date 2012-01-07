#ifndef RENDER_EVENT_CLIENT_H
#define RENDER_EVENT_CLIENT_H

namespace render
{
    class Event;

    class EventClient
    {
    public:
        virtual ~EventClient(){}

        virtual void process(const Event &event) = 0;
    };
}

#endif
