#ifndef RENDER_EVENT_CLIENT_H
#define RENDER_EVENT_CLIENT_H

namespace render
{
    class KeyboardEvent;

    class EventClient
    {
    public:
        virtual ~EventClient(){}

        virtual void process(const KeyboardEvent &keyboardEvent) = 0;
    };
}

#endif
