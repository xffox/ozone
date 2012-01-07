#ifndef RENDER_EVENT_H
#define RENDER_EVENT_H

#include <memory>

namespace render
{
    class EventVisitor;

    class Event
    {
    public:
        virtual ~Event(){}

        virtual std::auto_ptr<Event> clone() const = 0;
        virtual void accept(EventVisitor &visitor) = 0;
    };
}

#endif
