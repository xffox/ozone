#ifndef RENDER_KEYBOARD_EVENT_H
#define RENDER_KEYBOARD_EVENT_H

#include "render/Event.h"

namespace render
{
    class KeyboardEvent: public Event
    {
    public:
        enum ModifiersFlags
        {
            SHIFT = 1,
            CTRL = 2,
            ALT = 4
        };

    public:
        KeyboardEvent(int key = 0, unsigned char modifiers = 0);

        virtual std::auto_ptr<Event> clone() const;
        virtual void accept(EventVisitor &visitor);

        int getKey() const
        {
            return key;
        }

        unsigned char getModifiers() const
        {
            return modifiers;
        }

    private:
        int key;
        unsigned char modifiers;
    };
}

#endif
