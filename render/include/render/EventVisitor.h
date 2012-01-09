#ifndef RENDER_EVENT_VISITOR_H
#define RENDER_EVENT_VISITOR_H

namespace render
{
    class KeyboardEvent;
    class MouseMotionEvent;

    class EventVisitor
    {
    public:
        virtual ~EventVisitor(){}

        virtual void visitKeyboardEvent(const KeyboardEvent&){}
        virtual void visitMouseMotionEvent(const MouseMotionEvent&){}
    };
}

#endif
