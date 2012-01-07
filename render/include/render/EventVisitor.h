#ifndef RENDER_EVENT_VISITOR_H
#define RENDER_EVENT_VISITOR_H

namespace render
{
    class KeyboardEvent;

    class EventVisitor
    {
    public:
        virtual ~EventVisitor(){}

        virtual void visitKeyboardEvent(const KeyboardEvent&){}
    };
}

#endif
