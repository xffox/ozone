#include "render/MouseMotionEvent.h"

#include "render/EventVisitor.h"

namespace render
{
    std::auto_ptr<Event> MouseMotionEvent::clone() const
    {
        return std::auto_ptr<Event>(new MouseMotionEvent(*this));
    }

    void MouseMotionEvent::accept(EventVisitor &visitor)
    {
        visitor.visitMouseMotionEvent(*this);
    }
}
