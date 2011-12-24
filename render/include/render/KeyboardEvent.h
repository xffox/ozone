#ifndef RENDER_KEYBOARD_EVENT_H
#define RENDER_KEYBOARD_EVENT_H

namespace render
{
    class KeyboardEvent
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
