#include "render/KeyboardEvent.h"

#include "render/EventVisitor.h"

namespace render
{

KeyboardEvent::KeyboardEvent(int key, unsigned char modifiers)
    :key(key), modifiers(modifiers)
{
}

std::auto_ptr<Event> KeyboardEvent::clone() const
{
    return std::auto_ptr<Event>(new KeyboardEvent(*this));
}

void KeyboardEvent::accept(EventVisitor &visitor)
{
    visitor.visitKeyboardEvent(*this);
}
}
