#ifndef RENDER_MOUSE_MOTION_EVENT_H
#define RENDER_MOUSE_MOTION_EVENT_H

#include "render/Event.h"

namespace render
{
    class MouseMotionEvent: public Event
    {
    public:
        MouseMotionEvent(int x, int y)
            :x(x), y(y)
        {
        }

        virtual std::auto_ptr<Event> clone() const;
        virtual void accept(EventVisitor &visitor);

        int getX() const
        {
            return x;
        }

        int getY() const
        {
            return y;
        }

    private:
        int x;
        int y;
    };
}

#endif
